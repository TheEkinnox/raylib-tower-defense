#pragma once
#include <string>
#include "PlayerHUD.h"
#include "ConfigTower.h"

namespace TD
{
	class Player
	{
	public:
		PlayerHUD		HUD;
		unsigned int	Money;
		unsigned int	BaseHealth;

		Player();
		~Player() = default;

		bool			Load(const std::string& fileName);
		void			BuyTower(ConfigTower configTower);
		void			Damage(unsigned int damage);
		void			AddMoney(unsigned int amount);
		void			RemoveMoney(unsigned int amount);
		void			Update();
		void			Clear();

	private:
		const int PLAYER_CONFIG_DATA_COUNT = 2;
	};
}
