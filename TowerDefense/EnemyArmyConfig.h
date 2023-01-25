#pragma once
#include <string>

#include "EnemyWave.h"

namespace TD
{
	struct EnemyArmyConfig
	{
		float					Warmup;
		std::vector<EnemyWave>	Waves;

		bool					LoadFromFile(const std::string& filePath);
	};
}
