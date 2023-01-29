#pragma once
#include "TowerButton.h"

namespace TD
{
	class RegularTowerButton : public TowerButton
	{
	public:
		RegularTowerButton(Vector2 relativePosition, HUDWindow& window);

	protected:
		void BuyTower() override;
	};
}
