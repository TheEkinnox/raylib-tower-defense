#pragma once
#include <string>
#include "PlayerHUD.h"

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
		template<typename T>
		T*				BuyTower();
		void			Damage(unsigned int damage);
		void			UpdateMoney(int amount);
		void			Update();
		void			Clear();

	private:
		const int PLAYER_CONFIG_DATA_COUNT = 2;
	};

	template<typename T>
	T* Player::BuyTower()
	{
		// TODO: Implement tower purchase
	}
}
