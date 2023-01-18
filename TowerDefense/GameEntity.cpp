#include "pch.h"
#include "GameEntity.h"

#include "Sprite.h"

namespace TD
{
	GameEntity::GameEntity(Sprite& sprite) : sprite(&sprite)
	{
	}

	const Sprite& GameEntity::GetSprite() const
	{
		return *sprite;
	}

	Vector2 GameEntity::GetPosition() const
	{
		return sprite->GetPosition();
	}

	void GameEntity::SetPosition(const Vector2 position)
	{
		sprite->SetPosition(position.x, position.y);
	}
}
