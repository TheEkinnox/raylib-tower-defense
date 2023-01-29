#pragma once
#include "TowerButton.h"

namespace TD
{
	class StunTowerButton : public TowerButton
	{
	public:
		StunTowerButton(Vector2 relativePosition, HUDWindow& window);

	protected:
		void BuyTower() override;
	};
}
