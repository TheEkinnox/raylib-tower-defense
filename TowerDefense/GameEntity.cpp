#include "pch.h"
#include "GameEntity.h"

#include "Sprite.h"
#include "TowerDefenseGameManager.h"

namespace TD
{
	GameEntity::GameEntity() : m_sprite(nullptr)
	{
	}

	GameEntity::GameEntity(Sprite& sprite) : m_sprite(&sprite)
	{
	}

	GameEntity::~GameEntity()
	{
		if (m_sprite == nullptr)
			return;

		Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();
		renderer.RemoveSprite(*m_sprite);
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
