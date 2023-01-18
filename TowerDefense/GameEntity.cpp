#include "pch.h"
#include "GameEntity.h"

#include "Sprite.h"

namespace TD
{
	GameEntity::GameEntity(Sprite& sprite) : m_sprite(&sprite)
	{
	}

	const Sprite& GameEntity::GetSprite() const
	{
		return *m_sprite;
	}

	Vector2 GameEntity::Position() const
	{
		return m_sprite->Position();
	}

	Vector2& GameEntity::Position()
	{
		return m_sprite->Position();
	}
}
