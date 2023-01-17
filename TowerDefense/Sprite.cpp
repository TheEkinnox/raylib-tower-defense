#include "pch.h"
#include <stdexcept>

#include "Sprite.h"

namespace TD
{
	Sprite::Sprite() : Sprite({ 0 }, {}, { 0, 0 })
	{
	}

	Sprite::Sprite(const Texture& texture, const Vector2& position,
		const Renderer::Layer layer, const float& rotation, const float& scale,
		const Color& tint) :
			Sprite(texture,
				Rectangle{ 0, 0,
					static_cast<float>(texture.width),
					static_cast<float>(texture.height) },
				position, layer, rotation, scale, tint)
	{
	}

	Sprite::Sprite(const Texture& spriteSheet, const Rectangle& spriteRect,
		const Vector2& position, const Renderer::Layer layer, const float& rotation,
		const float& scale, const Color& tint) : Layer(layer), m_position(position), m_rotation(rotation), m_scale(scale), m_tint(tint)
	{
		if (spriteSheet.id != 0 &&
			(spriteRect.x < 0 || spriteRect.x + spriteRect.width > static_cast<float>(spriteSheet.width) ||
				spriteRect.y < 0 || spriteRect.y + spriteRect.height > static_cast<float>(spriteSheet.height)))
		{
			throw std::invalid_argument("Unable to set texture - Sprite is outside of texture's bounds.");
		}

		m_spriteSheet = &spriteSheet;
		m_spriteRect = spriteRect;
	}

	Sprite::Sprite(const Sprite& other) = default;

	Sprite::Sprite(Sprite&& other) noexcept
		: Layer(other.Layer), m_spriteSheet(other.m_spriteSheet), m_spriteRect(other.m_spriteRect),
		m_position(other.m_position), m_rotation(other.m_rotation), m_scale(other.m_scale), m_tint(other.m_tint)
	{
	}

	Sprite& Sprite::operator=(const Sprite& other)
	{
		if (this == &other)
			return *this;

		m_spriteSheet = other.m_spriteSheet;
		m_spriteRect = other.m_spriteRect;
		m_position = other.m_position;
		m_rotation = other.m_rotation;
		m_scale = other.m_scale;
		m_tint = other.m_tint;

		return *this;
	}

	Sprite& Sprite::operator=(Sprite&& other) noexcept
	{
		if (this == &other)
			return *this;

		m_spriteSheet = other.m_spriteSheet;
		m_spriteRect = other.m_spriteRect;
		m_position = other.m_position;
		m_rotation = other.m_rotation;
		m_scale = other.m_scale;
		m_tint = other.m_tint;

		return *this;
	}

	Texture Sprite::GetTexture() const
	{
		return *m_spriteSheet;
	}

	Vector2 Sprite::GetPosition() const
	{
		return m_position;
	}

	void Sprite::SetPosition(const float& xPos, const float& yPos)
	{
		m_position = { xPos, yPos };
	}

	float Sprite::GetRotation() const
	{
		return m_rotation;
	}

	void Sprite::SetRotation(const float& rotation)
	{
		m_rotation = rotation;
	}

	float Sprite::GetScale() const
	{
		return m_scale;
	}

	void Sprite::SetScale(const float& scale)
	{
		m_scale = scale < 0 ? 0 : scale;
	}

	Color Sprite::GetTint() const
	{
		return m_tint;
	}

	void Sprite::SetTint(const Color& tint)
	{
		m_tint = tint;
	}

	void Sprite::Draw() const
	{
		if (m_spriteSheet->id == 0)
			throw std::invalid_argument("Can't draw a sprite with an unloaded texture");

		const Rectangle scaledRect = { m_position.x, m_position.y, m_spriteRect.width * m_scale, m_spriteRect.height * m_scale };

		DrawTexturePro(*m_spriteSheet, m_spriteRect, scaledRect, { 0, 0 }, m_rotation, m_tint);
	}
}
