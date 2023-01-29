#include "pch.h"
#include "StunTowerButton.h"

#include "StunTower.h"
#include "TowerDefenseGameManager.h"

namespace TD
{
	StunTowerButton::StunTowerButton(const Vector2 relativePosition, HUDWindow& window) :
		TowerButton(relativePosition, window, TowerType::STUNNING)
	{
	}

	void StunTowerButton::BuyTower()
	{
		Player& player = TowerDefenseGameManager::GetInstance().Player;
		player.BuyTower<StunTower>(m_towerConfig);
	}
}
