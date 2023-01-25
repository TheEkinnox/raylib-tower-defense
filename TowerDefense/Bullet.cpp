#include "pch.h"
#include <Vector/Vector2.h>

#include "Bullet.h"
#include "TowerDefenseGameManager.h"
#include "enemy.h"

namespace TD
{
	Bullet::Bullet(Sprite& sprite, ITower& parent) : dir(), sprite(&sprite), speed(0), parent(&parent)
	{
		const GameMap& map = TowerDefenseGameManager::GetInstance().Map;
		const float scale = map.GetScale();
		this->sprite->SetScale(scale);
	}

	Bullet::~Bullet()
	{
		TowerDefenseGameManager::GetInstance().GetRenderer().RemoveSprite(*sprite);
	}

	Vector2 Bullet::Position() const
	{
		return sprite->Position();
	}

	Vector2& Bullet::Position()
	{
		return sprite->Position();
	}

	void Bullet::Update()
	{
		Position().x += dir.x * speed * GetFrameTime();
		Position().y += dir.y * speed * GetFrameTime();

		TowerDefenseGameManager& gameManager = TowerDefenseGameManager::GetInstance();
		const GameMap& map = gameManager.Map;
		Renderer& renderer = gameManager.GetRenderer();

		const Vector2 cellPos = map.GetCellPosition(Position());

		if (cellPos.x < 0 || static_cast<uint32_t>(cellPos.x) > map.GetWidth() ||
			cellPos.y < 0 || static_cast<uint32_t>(cellPos.y) > map.GetHeight())
		{
			renderer.RemoveSprite(*sprite);
			SetActive(false);
		}

		Enemy* enemy = CheckCollision();

		if (enemy != nullptr)
		{
			if (parent != nullptr)
				parent->OnBulletCollision(*enemy);

			SetActive(false);
			sprite->SetScale(0);
		}
	};

	Enemy* Bullet::CheckCollision()
	{
		EnemyArmy& enemyArmy = TowerDefenseGameManager::GetInstance().EnemyArmy;
		const GameMap& map = TowerDefenseGameManager::GetInstance().Map;
		const float scale = map.GetScale();

		std::vector<Enemy*>& enemyList = enemyArmy.GetArmy();
		LibMath::Vector2 enemyPos;
		LibMath::Vector2 bulletPos(Position().x, Position().y);
		const float squaredRange = sprite->GetTexture().width * scale * sprite->GetTexture().height * scale;

		for (size_t i = 0; i < enemyList.size(); i++)
		{
			enemyPos = { enemyList[i]->Position().x, enemyList[i]->Position().y };

			if (bulletPos.distanceSquaredFrom(enemyPos) <= squaredRange)
				return enemyList[i];
		}
	
		return nullptr;
	}

}