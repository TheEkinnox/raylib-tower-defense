#pragma once

#include <raylib.h>

#include "Renderer.h"

namespace TD
{
	class Sprite
	{
	public:
		Renderer::Layer	Layer;

		Sprite();

		Sprite(Texture texture, Vector2 position, Renderer::Layer layer = 0);

		Sprite(Texture spriteSheet, Rectangle spriteRect, Vector2 position,
			Renderer::Layer layer = 0);

		Sprite(const Sprite& other) = default;
		Sprite(Sprite&& other) = default;

		~Sprite() = default;

		Sprite&		operator=(const Sprite& other);
		Sprite&		operator=(Sprite&& other) noexcept;

		Texture		GetTexture() const;

		Vector2		Position() const;
		Vector2&	Position();

		Vector2		GetOrigin() const;
		void		SetOrigin(float xOrigin, float yOrigin);

		Vector2		GetScale() const;
		void		SetScale(float scale);
		void		SetScale(float xScale, float yScale);

		float		GetRotation() const;
		void		SetRotation(float rotation);

		Color		GetTint() const;
		void		SetTint(Color tint);

		void		Draw() const;

	private:
		Texture		m_spriteSheet;
		Rectangle	m_spriteRect;
		Vector2		m_position;
		Vector2		m_origin = { 0, 0 };
		Vector2		m_scale = { 1.f, 1.f };
		float		m_rotation = 0;
		Color		m_tint = WHITE;
	};
}
