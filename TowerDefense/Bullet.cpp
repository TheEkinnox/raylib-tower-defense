#include "pch.h"
#include <Vector/Vector2.h>

#include "Bullet.h"
#include "TowerDefenseGameManager.h"
#include "enemy.h"

namespace TD
{
	Bullet::Bullet(Sprite& sprite, ITower& parent) :
		dir(), sprite(&sprite), speed(0), parent(&parent)
	{
		const GameMap& map = TowerDefenseGameManager::GetInstance().Map;
		const float scale = map.GetScale();
		this->sprite->SetScale(scale);
	}

	Bullet::~Bullet()
	{
		parent = nullptr;

		if (sprite == nullptr)
			return;

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
		if (parent == nullptr)
		{
			SetActive(false);
			return;
		}

		Position().x += dir.x * speed * GetFrameTime();
		Position().y += dir.y * speed * GetFrameTime();

		TowerDefenseGameManager& gameManager = TowerDefenseGameManager::GetInstance();
		const GameMap& map = gameManager.Map;
		Renderer& renderer = gameManager.GetRenderer();

		const Vector2 cellPos = map.GetCellPosition(Position());

		if (cellPos.x < 0 || static_cast<uint32_t>(cellPos.x) > map.GetWidth() ||
			cellPos.y < 0 || static_cast<uint32_t>(cellPos.y) > map.GetHeight())
		{
			SetActive(false);
			renderer.RemoveSprite(*sprite);
			return;
		}

		Enemy* enemy = CheckCollision();

		if (enemy != nullptr)
		{
			parent->OnBulletCollision(*enemy);
			SetActive(false);
		}
	}

	Enemy* Bullet::CheckCollision()
	{
		EnemyArmy& enemyArmy = TowerDefenseGameManager::GetInstance().EnemyArmy;
		const GameMap& map = TowerDefenseGameManager::GetInstance().Map;
		const float scale = map.GetScale();

		const std::vector<Enemy*>& enemyList = enemyArmy.GetArmy();
		const LibMath::Vector2 bulletPos(Position().x, Position().y);
		const float squaredRange = static_cast<float>(sprite->GetTexture().width) * scale
			* static_cast<float>(sprite->GetTexture().height) * scale;

		for (size_t i = 0; i < enemyList.size(); i++)
		{
			LibMath::Vector2 enemyPos = {enemyList[i]->Position().x, enemyList[i]->Position().y};

			if (bulletPos.distanceSquaredFrom(enemyPos) <= squaredRange)
				return enemyList[i];
		}
	
		return nullptr;
	}

	void Bullet::SetActive(const bool active)
	{
		PooledObject::SetActive(active);

		if (sprite != nullptr)
		{
			if (active)
			{
				const GameMap& map = TowerDefenseGameManager::GetInstance().Map;
				const float scale = map.GetScale();
				sprite->SetScale(scale);
			}
			else
			{
				sprite->SetScale(0);
			}
		}

		if (!active)
			parent = nullptr;
	}
}