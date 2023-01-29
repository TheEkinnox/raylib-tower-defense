#include "pch.h"
#include "PoisonTowerButton.h"

#include "PoisonTower.h"
#include "TowerDefenseGameManager.h"

namespace TD
{
	PoisonTowerButton::PoisonTowerButton(const Vector2 relativePosition, HUDWindow& window) :
		TowerButton(relativePosition, window, TowerType::POISON)
	{
	}

	void PoisonTowerButton::BuyTower()
	{
		Player& player = TowerDefenseGameManager::GetInstance().Player;
		player.BuyTower<PoisonTower>(m_towerConfig);
	}
}
