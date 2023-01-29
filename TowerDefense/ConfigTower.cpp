#include "pch.h"
#include <fstream>
#include <raylib.h>

#include "utility.h"
#include "ConfigTower.h"

namespace TD
{
	bool ConfigTower::LoadFromFile(const TowerType type, const std::uint8_t level)
	{
		char const* configPath = TextFormat(TOWER_CONFIG_PATH_FORMAT, type, level);

		std::ifstream fileStream(configPath);

		if (!fileStream.is_open())
			return false;

		bulletType = type;

		std::string curLine;
		int loadedCount = 0;
		
		while (std::getline(fileStream, curLine) && loadedCount < TOWER_CONFIG_DATA_COUNT)
		{
			curLine = Trim(RemoveComments(curLine));

			if (curLine.empty())
				continue;

			std::vector<std::string> tokens = SplitString(curLine, " ", false);

			if (tokens.size() < 2 &&
				!(tokens.size() == 1 && tokens[0] == "bulletTexture"))
				continue;

			if (tokens[0] == "firingRate")
			{
				firingRate = std::stof(tokens[1]);
				loadedCount++;
			}
			else if (tokens[0] == "damage")
			{
				damage = std::stoul(tokens[1]);
				loadedCount++;
			}
			else if (tokens[0] == "range")
			{
				range = std::stof(tokens[1]);
				loadedCount++;
			}
			else if (tokens[0] == "maxLevel")
			{
				maxLevel = std::stoul(tokens[1]);
				loadedCount++;
			}
			else if (tokens[0] == "price")
			{
				price = std::stoul(tokens[1]);
				loadedCount++;
			}
			else if (tokens[0] == "sellPrice")
			{
				sellPrice = std::stoul(tokens[1]);
				loadedCount++;
			}
			else if (tokens[0] == "bulletSpeed")
			{
				bulletSpeed = std::stof(tokens[1]);
				loadedCount++;
			}
			else if (tokens[0] == "texture")
			{
				texturePath = TrimLeft(curLine.substr(tokens[0].size()));
				loadedCount++;
			}
			else if (tokens[0] == "buttonTexture")
			{
				buttonTexturePath = TrimLeft(curLine.substr(tokens[0].size()));
				loadedCount++;
			}
			else if (tokens[0] == "bulletTexture")
			{
				bulletTexturePath = TrimLeft(curLine.substr(tokens[0].size()));
				loadedCount++;
			}
		}

		return loadedCount == TOWER_CONFIG_DATA_COUNT;
	}
}
