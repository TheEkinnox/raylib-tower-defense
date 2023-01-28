#include "pch.h"
#include <fstream>

#include "Player.h"
#include "utility.h"
#include "TowerDefenseGameManager.h"

namespace TD
{
	Player::Player() : Money(0), BaseHealth(0)
	{
	}

	bool Player::Load(const std::string& fileName)
	{
		if (fileName.empty())
			return false;

		std::ifstream fileStream(fileName.c_str());

		if (!fileStream.is_open())
			return false;

		std::string	curLine;
		int loadedCount = 0;

		while (std::getline(fileStream, curLine) && loadedCount < PLAYER_CONFIG_DATA_COUNT)
		{
			curLine = Trim(RemoveComments(curLine));

			if (curLine.empty())
				continue;

			std::vector<std::string> tokens = SplitString(curLine, " ", false);

			if (tokens.size() < 2)
				continue;

			if (tokens[0] == "hq_init_life")
			{
				BaseHealth = std::stoul(tokens[1]);
				loadedCount++;
			}
			else if (tokens[0] == "budget")
			{
				Money = std::stoul(tokens[1]);
				loadedCount++;
			}
		}
		return loadedCount == PLAYER_CONFIG_DATA_COUNT;
	}

	void Player::Damage(const unsigned int damage)
	{
		BaseHealth = damage < BaseHealth ? BaseHealth - damage : 0;

		if (BaseHealth == 0)
			TowerDefenseGameManager::GetInstance().SetCurrentState(GameState::GAME_OVER);
	}

	void Player::UpdateMoney(const int amount)
	{
		Money = std::max(0U, Money + amount);
	}

	void Player::Update()
	{
		HUD.Update();
	}

	void Player::Clear()
	{
		HUD.ClearWindows();
		Money = 0;
		BaseHealth = 0;
	}
}
