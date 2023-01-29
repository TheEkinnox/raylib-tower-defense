#include "pch.h"
#include <Vector/Vector2.h>
#include "TowerDefenseGameManager.h"
#include "PoisonTower.h"
#include "ConfigTower.h"


namespace TD
{
	PoisonTower::PoisonTower(Vector2 position) :
		ITower(position, TowerType::POISON)
	{
	}

	void PoisonTower::ShootAt(const Enemy& enemy)
	{
		if (GetTime() < m_nextShootTime)
			return;

		EnemyArmy& enemyArmy = TowerDefenseGameManager::GetInstance().EnemyArmy;
		const GameMap& map = TowerDefenseGameManager::GetInstance().Map;
		const float scale = map.GetScale();

		const std::vector<Enemy*>& enemyList = enemyArmy.GetArmy();
		const LibMath::Vector2 towerPos(Position().x, Position().y);
		const float squaredRange = config.range * config.range * TILE_WIDTH * scale * TILE_HEIGHT * scale;

		for (size_t i = 0; i < enemyList.size(); i++)
		{
			LibMath::Vector2 enemyPos = { enemyList[i]->Position().x, enemyList[i]->Position().y };

			if (towerPos.distanceSquaredFrom(enemyPos) <= squaredRange)
				enemyList[i]->Damage(config.damage);
		}

		m_nextShootTime = GetTime() + static_cast<double>(1 / config.firingRate);
	};

	void PoisonTower::Update()
	{
		if (IsKeyPressed(KEY_FOUR))
			LevelUp();

		ITower::Update();
	}

	void PoisonTower::OnBulletCollision(Enemy& enemy)
	{
	}
}