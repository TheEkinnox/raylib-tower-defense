#include "pch.h"
#include <raylib.h>
#include "EnemyWave.h"

#include "EnemyArmy.h"
#include "HealerEnemy.h"

namespace TD
{
	EnemyWave::EnemyWave(const float delay) : Delay(delay)
	{
	}

	void EnemyWave::Update(EnemyArmy& army)
	{
		const float frameTime = GetFrameTime();

		if (Delay > 0)
		{
			Delay -= frameTime;
			return;
		}

		for (size_t i = 0; i < Enemies.size(); i++)
		{
			std::pair<EnemyType, float>& pair = Enemies[i];

			if (pair.second > 0)
			{
				pair.second -= frameTime;
			}
			else
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

				Enemies.erase(Enemies.begin() + i);
				i--;
			}
		}
	}
}
