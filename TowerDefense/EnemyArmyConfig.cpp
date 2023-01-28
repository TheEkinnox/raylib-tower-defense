#include "pch.h"
#include "EnemyArmyConfig.h"

#include <fstream>

#include "utility.h"

namespace TD
{
	bool EnemyArmyConfig::LoadFromFile(const std::string& filePath)
	{
		std::ifstream fileStream(filePath);

		if (!fileStream.is_open())
			return false;

		std::string	curLine;
		size_t curWave = 0;
		size_t enemyCount = 0;

		while (std::getline(fileStream, curLine))
		{
			curLine = Trim(RemoveComments(curLine));

			if (curLine.empty())
				continue;

			const std::vector<std::string> tokens = SplitString(curLine, " ", false);

			if (tokens[0] == "warmup")
			{
				if (tokens.size() < 2)
					return false;

				Warmup = std::stof(tokens[1]);
			}
			else if (tokens[0] == "wave")
			{
				if (tokens.size() < 2)
					return false;

				curWave = Waves.size();
				enemyCount = 0;

				Waves.emplace_back(std::stof(tokens[1]));
			}
			else if (tokens[0] == "enemy")
			{
				if (Waves.empty() || tokens.size() < 3)
					return false;

				EnemyType type = static_cast<EnemyType>(std::stoul(tokens[1]));
				float delay = std::stof(tokens[2]);

				Waves[curWave].EnemiesToSpawn.emplace_back(type, delay);
				enemyCount++;
			}
		}

		return true;
	}
}
