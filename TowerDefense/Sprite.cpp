#include "pch.h"
#include <stdexcept>

#include "Sprite.h"

namespace TD
{
	Sprite::Sprite() : Sprite({}, {}, { 0, 0 })
	{
	}

	Sprite::Sprite(const Texture texture, const Vector2 position,
		const TD::Layer layer) :
			Sprite(texture,
				Rectangle{ 0, 0,
					static_cast<float>(texture.width),
					static_cast<float>(texture.height) },
				position, layer)
	{
	}

	Sprite::Sprite(const Texture spriteSheet, const Rectangle spriteRect,
		const Vector2 position, const TD::Layer layer) : Layer(layer),
		m_spriteSheet(spriteSheet), m_spriteRect(spriteRect), m_position(position)
	{
		SetTexture(spriteSheet, spriteRect);
	}

	Sprite& Sprite::operator=(const Sprite& other)
	{
		if (this == &other)
			return *this;

		m_spriteSheet = other.m_spriteSheet;
		m_spriteRect = other.m_spriteRect;
		m_position = other.m_position;
		m_rotation = other.m_rotation;
		m_origin = other.m_origin;
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
		m_origin = other.m_origin;
		m_scale = other.m_scale;
		m_tint = other.m_tint;

		return *this;
	}

	Texture Sprite::GetTexture() const
	{
		return m_spriteSheet;
	}

	Sprite& Sprite::SetTexture(const Texture texture)
	{
		const Rectangle spriteRect
		{
			0,
			0,
			static_cast<float>(texture.width),
			static_cast<float>(texture.height)
		};

		SetTexture(texture, spriteRect);
		return *this;
	}

	Sprite& Sprite::SetTexture(const Texture texture, const Rectangle spriteRect)
	{
		if (texture.id != 0 &&
			(spriteRect.x < 0 || spriteRect.x + spriteRect.width > static_cast<float>(texture.width) ||
				spriteRect.y < 0 || spriteRect.y + spriteRect.height > static_cast<float>(texture.height)))
		{
			throw std::invalid_argument("Unable to set texture - Sprite is outside of texture's bounds.");
		}

		m_spriteSheet = texture;
		m_spriteRect = spriteRect;
		return *this;
	}

	Vector2 Sprite::Position() const
	{
		return m_position;
	}

	Vector2& Sprite::Position()
	{
		return m_position;
	}

	Vector2 Sprite::GetOrigin() const
	{
		return m_origin;
	}

	Sprite& Sprite::SetOrigin(const float xOrigin, const float yOrigin)
	{
		m_origin = { xOrigin, yOrigin };
		return *this;
	}

	Vector2 Sprite::GetScale() const
	{
		return m_scale;
	}

	Sprite& Sprite::SetScale(const float scale)
	{
		SetScale(scale, scale);
		return *this;
	}

	Sprite& Sprite::SetScale(const float xScale, const float yScale)
	{
		m_scale = { xScale, yScale };
		return *this;
	}

	float Sprite::GetRotation() const
	{
		return m_rotation;
	}

	Sprite& Sprite::SetRotation(const float rotation)
	{
		m_rotation = rotation;
		return *this;
	}

	Color Sprite::GetTint() const
	{
		return m_tint;
	}

	Sprite& Sprite::SetTint(const Color tint)
	{
		m_tint = tint;
		return *this;
	}

	Sprite& Sprite::Show()
	{
		m_isVisible = true;
		return *this;
	}

	Sprite& Sprite::Hide()
	{
		m_isVisible = false;
		return *this;
	}

	void Sprite::Draw() const
	{
		if (m_spriteSheet.id == 0)
			throw std::invalid_argument("Can't draw a sprite with an unloaded texture");

		if (!m_isVisible)
			return;

		const bool flipX = m_scale.x < 0;
		const bool flipY = m_scale.y < 0;

		const Rectangle sourceRect = {
			m_spriteRect.x, m_spriteRect.y,
			m_spriteRect.width * (flipX ? -1.f : 1.f),
			m_spriteRect.height * (flipY ? -1.f : 1.f)
		};

		const Rectangle scaledRect = {
			m_position.x, m_position.y,
			m_spriteRect.width * fabsf(m_scale.x),
			m_spriteRect.height * fabsf(m_scale.y)
		};

		const Vector2 origin = {
			static_cast<float>(scaledRect.width) * m_origin.x,
			static_cast<float>(scaledRect.height) * m_origin.y
		};

		DrawTexturePro(m_spriteSheet, sourceRect, scaledRect, origin, m_rotation, m_tint);
	}
}
