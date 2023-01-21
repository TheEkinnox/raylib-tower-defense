#include "pch.h"
#include "Renderer.h"

#include "Sprite.h"

namespace TD
{
	Renderer::Renderer() :
		m_target(LoadRenderTexture(GetScreenWidth(), GetScreenHeight()))
	{
	}

	Renderer::~Renderer()
	{
		for (auto& layerSprites : m_sprites)
			for (const Sprite* sprite : layerSprites)
				delete sprite;

		for (const auto& pair : m_textures)
			UnloadTexture(pair.second);

		UnloadRenderTexture(m_target);

		m_sprites.clear();
		m_textures.clear();
	}

	Sprite& Renderer::CreateSprite(const Texture& texture, const Vector2 position,
		const Layer zLayer)
	{
		if (zLayer >= m_sprites.size())
			m_sprites.resize(static_cast<size_t>(zLayer) + 1);

		m_sprites[zLayer].push_back(new Sprite(texture, position, zLayer));

		return *m_sprites[zLayer].back();
	}

	void Renderer::RemoveSprite(Sprite& sprite)
	{
		if (sprite.Layer < 0 || sprite.Layer > m_sprites.size())
			return;

		m_sprites[sprite.Layer].remove(&sprite);
		delete& sprite;
	}

	const Texture* Renderer::LoadTextureFile(const std::string& name)
	{
		const Texture texture = LoadTexture(name.c_str());

		if (texture.id == 0)
			return nullptr;

		m_textures[name] = texture;
		return &m_textures[name];
	}

	const Texture* Renderer::GetTexture(const std::string& name)
	{
		if (m_textures.find(name) != m_textures.end())
			return &m_textures[name];

		return LoadTextureFile(name);
	}

	Vector2 Renderer::GetTextureScale(const float width, const float height) const
	{
		return {
			static_cast<float>(m_target.texture.width) / width,
			static_cast<float>(m_target.texture.height) / height
		};
	}

	void Renderer::DrawSprites() const
	{
		if (m_sprites.empty())
			return;

		BeginDrawing();

			BeginTextureMode(m_target);

				ClearBackground(RAYWHITE);

				for (auto& layerSprites : m_sprites)
					for (const Sprite* sprite : layerSprites)
						sprite->Draw();

			EndTextureMode();

		ClearBackground(BLACK);

		DrawTarget();

		EndDrawing();
	}

	void Renderer::DrawTarget() const
	{
		Vector2 scale{
			static_cast<float>(GetScreenWidth()) / static_cast<float>(m_target.texture.width),
			static_cast<float>(GetScreenHeight()) / static_cast<float>(m_target.texture.height)
		};

		Vector2 pos{ 0, 0 };

		// determine the game's target and current aspect ratio
		const float targetAspect = static_cast<float>(m_target.texture.width) / static_cast<float>(m_target.texture.height);
		const float screenAspect = static_cast<float>(GetScreenWidth()) / static_cast<float>(GetScreenHeight());

		// current viewport height should be scaled by this amount
		const float heightScale = screenAspect / targetAspect;

		// if scaled height is less than current height, add letterbox (black bars on the top and bottom)
		if (heightScale < 1.f)
		{
			scale.y *= heightScale;
			pos.y = (1.f - heightScale) * .5f * static_cast<float>(GetScreenHeight());
		}
		else // add pillar-box (black bars on the left and right)
		{
			const float widthScale = 1.f / heightScale;
			scale.x *= widthScale;
			pos.x = (1.f - widthScale) * .5f * static_cast<float>(GetScreenWidth());
		}

		Sprite targetSprite = { m_target.texture, pos, 0 };

		// Flip the sprite since render textures are flipped by default
		targetSprite.SetScale(scale.x, -scale.y);
		targetSprite.Draw();
	}
}
