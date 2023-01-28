#pragma once

#include <raylib.h>
#include <string>
#include <vector>
#include <list>
#include <map>
#include "Layer.h"

namespace TD
{
	class Sprite;

	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		Sprite&							CreateSprite(const Texture& texture, Vector2 position, Layer zLayer = Layer::DEFAULT);
		void							RemoveSprite(const Sprite& sprite);
		const Texture*					LoadTextureFile(const std::string& name);
		const Texture*					GetTexture(const std::string& name);
		Vector2							GetRenderSize() const;
		Vector2							GetRenderScale() const;
		Vector2							GetRenderPosition() const;
		Vector2							GetTextureScale(float width, float height, Vector2 modifier = { 1, 1 }) const;
		void							DrawSprites() const;

	private:
		std::map<std::string, Texture>	m_textures;
		std::vector<std::list<Sprite*>>	m_sprites;
		RenderTexture					m_target;

		void							DrawTarget() const;
	};
}
