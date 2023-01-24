#pragma once
#include "EnemyConfig.h"
#include "GameEntity.h"

namespace TD
{
	class EnemyArmy;

	class Enemy : public GameEntity
	{
	public:
		Enemy(EnemyType type, EnemyArmy& army, Vector2 position);
		~Enemy() override;

		virtual void	Update();
		void			Damage(unsigned int damage);
		void			Heal(unsigned int amount);
		void			Stun(float duration);

	protected:
		EnemyConfig		m_config;
		EnemyArmy*		m_army;
		float			stunTime;
		double			m_nextHitTime;
	};
}
