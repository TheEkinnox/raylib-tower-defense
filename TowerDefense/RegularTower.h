#pragma once
#include "ITower.h"

namespace TD
{
	class RegularTower : public ITower
	{
	public:

		RegularTower(Vector2 position);

		void ShootAt(const Enemy& enemy) override;
		void Update() override;	// update the regular tower
		void OnBulletCollision(Enemy& enemy) override;
	};
}