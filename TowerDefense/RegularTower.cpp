#include "pch.h"
#include "TowerDefenseGameManager.h"
#include "RegularTower.h"
#include "ConfigTower.h"


namespace TD
{
	RegularTower::RegularTower(const Vector2 position) :
		ITower(position, TowerType::REGULAR)
	{
	}

	void RegularTower::Update()
	{
#ifdef _DEBUG
		if (IsKeyPressed(KEY_ONE))
			LevelUp();
#endif

		ITower::Update();
	}

	void RegularTower::OnBulletCollision(Enemy& enemy)
	{
		enemy.Damage(config.damage);
	}
}