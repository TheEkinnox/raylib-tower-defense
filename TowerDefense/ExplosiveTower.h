#pragma once
#include "ITower.h"
#include "Bullet.h"
#include "Vector/Vector2.h"

namespace TD
{
		class ExplosiveTower : public ITower
		{
		public:
			ExplosiveTower(Sprite&);

			void ShootAt();
			void Update() override;					//update de explosive tower
		};
}