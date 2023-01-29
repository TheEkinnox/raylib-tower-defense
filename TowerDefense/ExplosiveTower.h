#pragma once
#include "ITower.h"

namespace TD
{
		class ExplosiveTower : public ITower
		{
		public:
			explicit	ExplosiveTower(Vector2 position);

			void		Update() override;					//update de explosive tower
			void		OnBulletCollision(Enemy& enemy) override;
		};
}