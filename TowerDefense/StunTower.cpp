#include "pch.h"
#include "TowerDefenseGameManager.h"
#include "StunTower.h"
#include "ConfigTower.h"


namespace TD
{
	StunTower::StunTower(const Vector2 position) :
		ITower(position, TowerType::STUNNING)
	{
	}

	void StunTower::Update()
	{
#ifdef _DEBUG
		if (IsKeyPressed(KEY_TWO))
			LevelUp();
#endif

		ITower::Update();
	}

	void StunTower::OnBulletCollision(Enemy& enemy)
	{
		enemy.Stun(STUN_TIME);
		enemy.Damage(config.damage);
	}
}