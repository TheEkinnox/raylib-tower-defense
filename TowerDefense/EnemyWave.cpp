#include "pch.h"
#include <raylib.h>
#include "EnemyWave.h"

#include "EnemyArmy.h"
#include "HealerEnemy.h"

namespace TD
{
	EnemyWave::EnemyWave(const float delay) : Delay(delay), m_timer(0)
	{
	}

	void EnemyWave::Reset()
	{
		m_timer = 0;
		EnemiesToSpawn = SpawnedEnemies;
		SpawnedEnemies.clear();
	}

	void EnemyWave::Update(EnemyArmy& army)
	{
		m_timer += GetFrameTime();

		if (m_timer < Delay)
			return;

		for (size_t i = 0; i < EnemiesToSpawn.size(); i++)
		{
			const std::pair<EnemyType, float>& pair = EnemiesToSpawn[i];

			if (m_timer >= pair.second + Delay)
			{
				switch (pair.first)
				{
				case EnemyType::SCOUT:
				case EnemyType::TANK:
					army.SpawnEnemy<Enemy>(pair.first);
					break;
				case EnemyType::HEALER:
					army.SpawnEnemy<HealerEnemy>(pair.first);
					break;
				default:
					throw std::out_of_range("Invalid enemy type");
				}

				SpawnedEnemies.push_back(EnemiesToSpawn[i]);
				EnemiesToSpawn.erase(EnemiesToSpawn.begin() + i);
				i--;
			}
		}
	}
}
