#pragma once
#include "EnemyConfig.h"
#include "GameEntity.h"
#include "IPathFinder.h"

namespace TD
{
	class EnemyArmy;

	class Enemy : public GameEntity
	{
	public:
		Enemy(EnemyType type, EnemyArmy& army, Vector2 position);
		~Enemy() override;

		virtual void		Update();
		void				MoveTo(Vector2 cellPosition);
		void				Damage(unsigned int damage);
		void				Heal(unsigned int amount);
		void				Stun(float duration);
		void				HitHQ() const;

	protected:
		EnemyConfig			m_config;
		EnemyArmy*			m_army;
		ai::IPathFinder*	m_pathFinder;
		float				m_remainingStunTime;
	};
}
