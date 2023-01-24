#pragma once
#include "ITower.h"

#define STUN_TIME 1

namespace TD
{
	class StunTower : public ITower
	{
	public:

		StunTower(Vector2 position);

		void LevelUp();
		void ShootAt(const Enemy& enemy) override;
		void Update() override;	// update the regular tower
		void OnBulletCollision(Enemy& enemy) override;
	};

}