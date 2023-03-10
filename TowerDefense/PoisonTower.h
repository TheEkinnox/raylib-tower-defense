#pragma once
#include "ITower.h"

namespace TD
{
	class PoisonTower : public ITower
	{
	public:
		PoisonTower(Vector2 position);

		void ShootAt(const Enemy& enemy) override;
		void Update() override;					//update de explosive tower
		void OnBulletCollision(Enemy& enemy) override;
	};
}