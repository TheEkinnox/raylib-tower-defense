#include "pch.h"
#include "ExplosiveTowerButton.h"

#include "ExplosiveTower.h"
#include "TowerDefenseGameManager.h"

namespace TD
{
	ExplosiveTowerButton::ExplosiveTowerButton(const Vector2 relativePosition, HUDWindow& window) :
		TowerButton(relativePosition, window, TowerType::EXPLOSIVE)
	{
	}

	void ExplosiveTowerButton::BuyTower()
	{
		Player& player = TowerDefenseGameManager::GetInstance().Player;
		player.BuyTower<ExplosiveTower>(m_towerConfig);
	}
}
