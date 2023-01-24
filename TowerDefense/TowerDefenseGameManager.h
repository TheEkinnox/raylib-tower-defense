#pragma once
#include "GameMap.h"
#include "EnemyArmy.h"
#include "IGameManager.h"

namespace TD
{
	class TowerDefenseGameManager : public IGameManager
	{
	public:
		GameMap		Map;
		EnemyArmy	EnemyArmy;
	//	Player		Player;		// TODO: Uncomment this when Player is implemented

		TowerDefenseGameManager();

		void								Init(int argc = 0, char* const* argv = nullptr) override;
		void								Update() override;
		static TowerDefenseGameManager&		GetInstance();
		void								DrawTiles();
	};
}
