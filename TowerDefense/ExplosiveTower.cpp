#include "pch.h"
#include "TowerDefenseGameManager.h"
#include "ExplosiveTower.h"
#include "ConfigTower.h"


namespace TD
{
	ExplosiveTower::ExplosiveTower(const Vector2 position) :
		ITower(position, TowerType::EXPLOSIVE)
	{
	}

	void ExplosiveTower::Update()
	{
#ifdef _DEBUG
		if (IsKeyPressed(KEY_THREE))
			LevelUp();
#endif

		ITower::Update();
	}

	void ExplosiveTower::OnBulletCollision(Enemy& enemy)
	{
		EnemyArmy& enemyArmy = TowerDefenseGameManager::GetInstance().EnemyArmy;
		const GameMap& map = TowerDefenseGameManager::GetInstance().Map;

		const std::vector<Enemy*>& enemyList = enemyArmy.GetArmy();
		const Vector2 cellPosition = map.GetCellPosition(enemy.Position());

		for (size_t i = 0; i < enemyList.size(); i++)
		{
			const Vector2 enemyCell = map.GetCellPosition(enemyList[i]->Position());

			if (static_cast<unsigned int>(enemyCell.x) == static_cast<unsigned int>(cellPosition.x)
				&& static_cast<unsigned int>(enemyCell.y) == static_cast<unsigned int>(cellPosition.y))
				enemyList[i]->Damage(config.damage);
		}
	}
}