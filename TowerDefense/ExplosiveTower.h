#pragma once
#include "ITower.h"

namespace TD
{
		class ExplosiveTower : public ITower
		{
		public:
			
			ExplosiveTower(Vector2 position);

			void LevelUp();
			void ShootAt(const Enemy& enemy) override;
			void Update() override;					//update de explosive tower
			void OnBulletCollision(Enemy& enemy) override;
		};
}