#pragma once
#include "ITower.h"

namespace TD
{
	class RegularTower : public ITower
	{
	public:
		explicit	RegularTower(Vector2 position);

		void		Update() override;	// update the regular tower
		void		OnBulletCollision(Enemy& enemy) override;
	};
}