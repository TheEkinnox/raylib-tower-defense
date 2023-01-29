#pragma once
#include "TowerButton.h"

namespace TD
{
	class ExplosiveTowerButton : public TowerButton
	{
	public:
		ExplosiveTowerButton(Vector2 relativePosition, HUDWindow& window);

	protected:
		void BuyTower() override;
	};
}
