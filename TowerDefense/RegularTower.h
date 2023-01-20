#pragma once
#include "ITower.h"
#include "Bullet.h"
#include "Vector/Vector2.h"

namespace TD
{
	static Bullet *rBullet;
	class RegularTower : public ITower
		{
		public:
			RegularTower(Sprite&);

			void ShootAt();
			void Update() override;				// update the regular tower
		};
}