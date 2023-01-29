#pragma once
#include <iostream>
#include "GameEntity.h"
#include "Pool.h"
#include "ConfigTower.h"

using namespace std;

namespace TD
{
	class Enemy;

	class ITower : public GameEntity
	{
	public:
		std::uint8_t			level;
		unsigned int			upgradeCost;
		ConfigTower				config;

		~ITower() override;

		virtual void			Update();
		virtual void			LevelUp();
		virtual void			ShootAt(const Enemy& enemy) = 0;
		virtual void			OnBulletCollision(Enemy& enemy) = 0;

	protected:
		ITower(Vector2 position, TowerType type);

		double					m_nextShootTime;

		static	Pool<Bullet>	m_bulletPool;
		static	size_t			m_towersCount;

		Enemy*	CheckRange();
	};
}