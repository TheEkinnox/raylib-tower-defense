#pragma once
#include "TowerButton.h"

namespace TD
{
	class PoisonTowerButton : public TowerButton
	{
	public:
		PoisonTowerButton(Vector2 relativePosition, HUDWindow& window);

	protected:
		void BuyTower() override;
	};
}