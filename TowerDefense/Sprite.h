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

		Sprite(const Texture& texture, const Vector2& position = { 0, 0 },
			Renderer::Layer layer = 0, const float& rotation = 0,
			const float& scale = 1, const Color& tint = WHITE);

		Sprite(const Texture& spriteSheet, const Rectangle& spriteRect,
			const Vector2& position = { 0, 0 }, Renderer::Layer layer = 0,
			const float& rotation = 0, const float& scale = 1,
			const Color& tint = WHITE);

		Sprite(const Sprite& other);
		Sprite(Sprite&& other) noexcept;

		~Sprite() = default;

		Sprite& operator=(const Sprite& other);
		Sprite& operator=(Sprite&& other) noexcept;

		Texture	GetTexture() const;

		Vector2	GetPosition() const;
		void	SetPosition(const float& xPos, const float& yPos);

		float	GetRotation() const;
		void	SetRotation(const float& rotation);

		float	GetScale() const;
		void	SetScale(const float& scale);

		Color	GetTint() const;
		void	SetTint(const Color& tint);

		void	Draw() const;

	private:
		const Texture*	m_spriteSheet;
		Rectangle		m_spriteRect;
		Vector2			m_position;
		float			m_rotation;
		float			m_scale;
		Color			m_tint;
	};
}
