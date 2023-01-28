#pragma once
#include "Player.h"
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
		Player		Player;

		TowerDefenseGameManager();

		void							Init(int argc = 0, char* const* argv = nullptr) override;
		void							LoadLevel(const std::string& configPath);
		void							HandleDevShortcuts();
		void							Update() override;
		void							SetCurrentState(GameState state) override;
		std::string						GetCurrentLevel() const;
		static TowerDefenseGameManager&	GetInstance();

	private:
		std::string						m_currentLevelPath;
	};
}
