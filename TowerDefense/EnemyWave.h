#pragma once
#include <vector>

#include "EnemyType.h"

namespace TD
{
	class EnemyArmy;

	class EnemyWave
	{
	public:
		// A pair containing the type of the enemy and the time it takes to spawn after the wave starts
		typedef std::pair<EnemyType, float> WaveDataPair;

		explicit					EnemyWave(float delay);

		float						Delay;
		std::vector<WaveDataPair>	EnemiesToSpawn;
		std::vector<WaveDataPair>	SpawnedEnemies;

		void						Reset();
		void						Update(EnemyArmy& army);

	private:
		float						m_timer;
	};
}
