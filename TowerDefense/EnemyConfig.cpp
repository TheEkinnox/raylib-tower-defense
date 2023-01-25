#include "pch.h"
#include <raylib.h>
#include <fstream>
#include <vector>

#include "EnemyConfig.h"
#include "utility.h"

namespace TD
{
	EnemyConfig::EnemyConfig(const EnemyType type) :
		Type(type), Speed(0), Damage(0), Gold(0), Life(0), MaxLife(0)
	{
	}

	bool EnemyConfig::LoadFromFile()
	{
		char const* configPath = TextFormat(ENEMY_CONFIG_PATH_FORMAT, Type);

		std::ifstream fileStream(configPath);

		if (!fileStream.is_open())
			return false;

		std::string	curLine;
		int loadedCount = 0;

		while (std::getline(fileStream, curLine) &&
			loadedCount < ENEMY_CONFIG_DATA_COUNT)
		{
			curLine = Trim(RemoveComments(curLine));

			if (TryLoadMember(curLine))
				loadedCount++;
		}

		return loadedCount == ENEMY_CONFIG_DATA_COUNT;
	}

	bool EnemyConfig::TryLoadMember(const std::string& line)
	{
		if (line.empty())
			return false;

		const std::vector<std::string> tokens = SplitString(line, " ", false);

		if (tokens.size() < 2)
			return false;

		if (tokens[0] == "texture")
			TexturePath = TrimLeft(line.substr(tokens[0].size())); 
		else if (tokens[0] == "speed")
			Speed = std::stof(tokens[1]);
		else if (tokens[0] == "damage")
			Damage = std::stoul(tokens[1]);
		else if (tokens[0] == "gold")
			Gold = std::stoul(tokens[1]);
		else if (tokens[0] == "health")
			Life = MaxLife = std::stoul(tokens[1]);
		else
			return false;

		return true;
	}
}
