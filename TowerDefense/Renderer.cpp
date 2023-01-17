#include "pch.h"
#include "Renderer.h"

#include "Sprite.h"

TD::Renderer::Renderer() :
	m_target(LoadRenderTexture(GetRenderWidth(), GetRenderHeight()))
{
	m_sprites.resize(UINT8_MAX);
}

TD::Renderer::~Renderer()
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

TD::Sprite& TD::Renderer::CreateSprite(const Texture& texture, Vector2 position, Layer zLayer)
{
	m_sprites[zLayer].push_back(new Sprite(texture, position, zLayer));

	return *m_sprites[zLayer].back();
}

void TD::Renderer::RemoveSprite(Sprite& sprite)
{
	if (sprite.Layer < 0 || sprite.Layer > m_sprites.size())
		return;

	m_sprites[sprite.Layer].remove(&sprite);
	delete& sprite;
}

const Texture* TD::Renderer::LoadTextureFile(const std::string& name)
{
	if (m_textures.find(name) == m_textures.end())
		m_textures[name] = LoadTexture(name.c_str());

	return &m_textures[name];
}

const Texture* TD::Renderer::GetTexture(const std::string& name)
{
	return &m_textures[name];
}

void TD::Renderer::DrawSprites() const
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
	EndDrawing();
}
