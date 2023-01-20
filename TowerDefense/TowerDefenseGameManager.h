#pragma once
#include "GameMap.h"
#include "IGameManager.h"

namespace TD
{
	class TowerDefenseGameManager : public IGameManager
	{
	public:
		GameMap		Map;
	//	EnemyArmy	EnemyArmy;	// TODO: Uncomment this line when EnemyArmy is implemented
	//	Player		Player;		// TODO: Uncomment this when Player is implemented

		TowerDefenseGameManager();

		void								Init() override;
		void								Update() override;
		static	TowerDefenseGameManager&	GetInstance();
		void DrawTiles();
	};
}
