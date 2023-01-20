#pragma once
#include <iostream>
#include "GameEntity.h"
#include "Pool.h"

using namespace std;

namespace TD
{
	class ITower : public GameEntity
	{
	public:
		//price : unsigned int price;
		//level : std::uint8_t
		//UpdateCost : unsigned int UpdateCost;
		//config : ConfigTower

		virtual void Update() = 0;
		//ShootAt(TD::Enemy const&) : void = 0
		//LevelUp : void = 0 
	protected:
		ITower(Sprite& sprite);

		Pool<Bullet> m_bulletPool;
		//CheckRange() : TD::Enemy*
	};
}