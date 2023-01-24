#include "pch.h"
#include <raylib.h>
#include <Vector.h>

#include "TowerDefenseGameManager.h"
#include "ITower.h"

namespace TD
{
	Pool<Bullet> ITower::m_bulletPool{};

	ITower::ITower() : level(1), config(), m_nextShootTime(), upgradeCost()
	{
	}

	Enemy* ITower::CheckRange()
	{
		EnemyArmy& enemyArmy = TowerDefenseGameManager::GetInstance().EnemyArmy;
		const GameMap& map = TowerDefenseGameManager::GetInstance().Map;
		const float scale = map.GetScale();

		std::vector<Enemy*>& enemyList = enemyArmy.GetArmy();
		LibMath::Vector2 enemyPos;
		LibMath::Vector2 towerPos(Position().x, Position().y);
		const float squaredRange = config.range * config.range * TILE_WIDTH * scale * TILE_HEIGHT * scale;

		for (size_t i = 0; i < enemyList.size(); i++)
		{
			enemyPos = {enemyList[i]->Position().x, enemyList[i]->Position().y};

			if (towerPos.distanceSquaredFrom(enemyPos) <= squaredRange)
				return enemyList[i];
		}
		return nullptr;
	}
}