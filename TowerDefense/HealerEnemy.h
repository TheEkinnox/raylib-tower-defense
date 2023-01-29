#pragma once
#include "Enemy.h"

#define HEALER_DATA_COUNT 3

namespace TD
{
	class HealerEnemy : public Enemy
	{
	public:
		HealerEnemy(EnemyType type, EnemyArmy& army, Vector2 position);

		void			HealAround();
		void			Update() override;

	private:
		float			m_healRange;
		unsigned int	m_healAmount;
		float			m_healCooldown;
		float			m_healTimer;
	};
}
