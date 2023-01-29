#include "pch.h"
#include "RegularTowerButton.h"

#include "RegularTower.h"
#include "TowerDefenseGameManager.h"

namespace TD
{
	RegularTowerButton::RegularTowerButton(const Vector2 relativePosition, HUDWindow& window) :
		TowerButton(relativePosition, window, TowerType::REGULAR)
	{
	}

	void RegularTowerButton::BuyTower()
	{
		Player& player = TowerDefenseGameManager::GetInstance().Player;
		player.BuyTower<RegularTower>(m_towerConfig);
	}
}
