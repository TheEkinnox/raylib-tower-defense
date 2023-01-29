#pragma once
#include "ITower.h"

#define STUN_TIME 1

namespace TD
{
	class StunTower : public ITower
	{
	public:
		explicit	StunTower(Vector2 position);

		void		Update() override;	// update the regular tower
		void		OnBulletCollision(Enemy& enemy) override;
	};
}