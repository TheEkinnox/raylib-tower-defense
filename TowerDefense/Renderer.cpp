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
		const size_t layer = static_cast<size_t>(zLayer);

		if (layer >= m_sprites.size())
			m_sprites.resize(layer + 1);

		m_sprites[layer].push_back(new Sprite(texture, position, zLayer));

		return *m_sprites[layer].back();
	}

	void Renderer::RemoveSprite(const Sprite& sprite)
	{
		const size_t layer = static_cast<size_t>(sprite.Layer);

		if (layer < 0 || layer > m_sprites.size())
			return;

		for (Sprite* layerSprite : m_sprites[layer])
		{
			if (layerSprite != nullptr && layerSprite == &sprite)
			{
				m_sprites[layer].remove(layerSprite);
				delete layerSprite;
				return;
			}
		}
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

	Vector2 Renderer::GetRenderSize() const
	{
		return {
			static_cast<float>(m_target.texture.width),
			static_cast<float>(m_target.texture.height)
		};
	}

	Vector2 Renderer::GetRenderScale() const
	{
		Vector2 scale{
			static_cast<float>(GetScreenWidth()) / static_cast<float>(m_target.texture.width),
			static_cast<float>(GetScreenHeight()) / static_cast<float>(m_target.texture.height)
		};

		// determine the game's target and current aspect ratio
		const float targetAspect = static_cast<float>(m_target.texture.width) / static_cast<float>(m_target.texture.height);
		const float screenAspect = static_cast<float>(GetScreenWidth()) / static_cast<float>(GetScreenHeight());

		// current viewport height should be scaled by this amount
		const float heightScale = screenAspect / targetAspect;

		// if scaled height is less than current height, add letterbox (black bars on the top and bottom)
		if (heightScale < 1.f)
			scale.y *= heightScale;
		else // add pillar-box (black bars on the left and right)
			scale.x *= 1.f / heightScale;

		return scale;
	}

	Vector2 Renderer::GetRenderPosition() const
	{
		Vector2 pos{ 0, 0 };

		// determine the game's target and current aspect ratio
		const float targetAspect = static_cast<float>(m_target.texture.width) / static_cast<float>(m_target.texture.height);
		const float screenAspect = static_cast<float>(GetScreenWidth()) / static_cast<float>(GetScreenHeight());

		// current viewport height should be scaled by this amount
		const float heightScale = screenAspect / targetAspect;

		// if scaled height is less than current height, add letterbox (black bars on the top and bottom)
		if (heightScale < 1.f)
			pos.y = (1.f - heightScale) * .5f * static_cast<float>(GetScreenHeight());
		else // add pillar-box (black bars on the left and right)
			pos.x = (1.f - 1.f / heightScale) * .5f * static_cast<float>(GetScreenWidth());

		return pos;
	}

	Vector2 Renderer::GetTextureScale(const float width, const float height, const Vector2 modifier) const
	{
		return {
			static_cast<float>(m_target.texture.width) * modifier.x / width,
			static_cast<float>(m_target.texture.height) * modifier.y / height
		};
	}

	void Renderer::DrawSprites() const
	{
		if (m_sprites.empty())
			return;

		BeginDrawing();

			BeginTextureMode(m_target);

				ClearBackground(WHITE);

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
		const Vector2 scale = GetRenderScale();
		const Vector2 pos = GetRenderPosition();

		Sprite targetSprite = { m_target.texture, pos, Layer::DEFAULT };

		// Flip the sprite since render textures are flipped by default
		targetSprite.SetScale(scale.x, -scale.y);
		targetSprite.SetOrigin(0, 0);
		targetSprite.Draw();
	}
}
