#pragma once
#include <iostream>

#include "Bullet.h"
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
		static void				UpdateBullets();
		virtual void			LevelUp();
		virtual void			ShootAt(const Enemy& enemy);
		virtual void			OnBulletCollision(Enemy& enemy) = 0;

	protected:
		ITower(Vector2 position, TowerType type);

		float					m_shootTimer;
		Sprite*					m_rangeSprite;
		RenderTexture			m_rangeTexture;

		static	Pool<Bullet>	m_bulletPool;
		static	size_t			m_towersCount;

		Enemy*					CheckRange();
		void					GenerateRangeTexture();

	private:
		static constexpr size_t	BULLET_POOL_START_SIZE = 32;
		static constexpr float	RANGE_CIRCLE_THICKNESS = 4;
	};
}