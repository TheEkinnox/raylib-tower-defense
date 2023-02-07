#pragma once

#include <raylib.h>

#include "Layer.h"

namespace TD
{
	class Sprite
	{
	public:
		Layer	Layer;

		Sprite();

		Sprite(Texture texture, Vector2 position, TD::Layer layer = Layer::DEFAULT);

		Sprite(Texture spriteSheet, Rectangle spriteRect, Vector2 position,
			TD::Layer layer = Layer::DEFAULT);

		Sprite(const Sprite& other) = default;
		Sprite(Sprite&& other) = default;

		~Sprite() = default;

		Sprite&		operator=(const Sprite& other);
		Sprite&		operator=(Sprite&& other) noexcept;

		Texture		GetTexture() const;
		Sprite&		SetTexture(Texture texture);
		Sprite&		SetTexture(Texture texture, Rectangle spriteRect);

		Vector2		Position() const;
		Vector2&	Position();

		Vector2		GetOrigin() const;
		Sprite&		SetOrigin(float xOrigin, float yOrigin);

		Vector2		GetScale() const;
		Sprite&		SetScale(float scale);
		Sprite&		SetScale(float xScale, float yScale);

		float		GetRotation() const;
		Sprite&		SetRotation(float rotation);

		Color		GetTint() const;
		Sprite&		SetTint(Color tint);

		Sprite&		Show();
		Sprite&		Hide();

		void		Draw() const;

	private:
		Texture		m_spriteSheet;
		Rectangle	m_spriteRect;
		Vector2		m_position;
		Vector2		m_origin = { .5f, .5f };
		Vector2		m_scale = { 1.f, 1.f };
		float		m_rotation = 0;
		Color		m_tint = WHITE;
		bool		m_isVisible = true;
	};
}
