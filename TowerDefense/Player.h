#pragma once
#include <string>
#include "PlayerHUD.h"
#include "ConfigTower.h"
#include "GameMap.h"

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

		template		<typename T>
		void			BuyTower(const ConfigTower& configTower);

		void			Damage(unsigned int damage);
		void			AddMoney(unsigned int amount);
		void			RemoveMoney(unsigned int amount);
		void			Update();
		void			Clear();

	private:
		const int PLAYER_CONFIG_DATA_COUNT = 2;

		GameMap&		GetMap();
	};

	template <typename T>
	void Player::BuyTower(const ConfigTower& configTower)
	{
		if (Money < configTower.price)
			return;

		GameMap& map = GetMap();

		const T* addedTower = map.AddTower<T>(map.GetMouseCellPosition());

		if (addedTower != nullptr)
			RemoveMoney(configTower.price);
	}
}
