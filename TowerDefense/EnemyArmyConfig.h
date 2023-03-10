#pragma once
#include <string>

#include "EnemyWave.h"

namespace TD
{
	struct EnemyArmyConfig
	{
		float					Warmup = 0;
		float					WaveHealthModifier = 1;
		std::vector<EnemyWave>	Waves;

		bool					LoadFromFile(const std::string& filePath);
	};
}
