#pragma once

#include <raylib.h>
#include <string>
#include <vector>
#include <list>
#include <map>

namespace TD
{
	class Sprite;

	class Renderer
	{
	public:
		typedef std::uint8_t Layer;

		Renderer();
		~Renderer();

		Sprite&							CreateSprite(const Texture& texture, Vector2 position, Layer zLayer = 0);
		void							RemoveSprite(const Sprite& sprite);
		const Texture*					LoadTextureFile(const std::string& name);
		const Texture*					GetTexture(const std::string& name);
		Vector2							GetRenderSize() const;
		Vector2							GetTextureScale(float width, float height) const;
		void							DrawSprites() const;

	private:
		std::map<std::string, Texture>	m_textures;
		std::vector<std::list<Sprite*>>	m_sprites;
		RenderTexture					m_target;

		void							DrawTarget() const;
	};
}
