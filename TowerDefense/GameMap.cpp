#include "pch.h"
#include <fstream>

#include "GameMap.h"

#include "utility.h"

TD::GameMap::GameMap() : m_width(0), m_height(0)
{
}

TD::GameMap::~GameMap()
{
	Clear();
}

bool TD::GameMap::BuildFromFile(const std::string& fileName)
{
	if (fileName.empty())
		return false;

	std::ifstream fileStream(fileName.c_str());

	if (!fileStream.is_open())
		return false;

	std::string	curLine;

	while(std::getline(fileStream, curLine))
	{
		curLine = Trim(RemoveComments(curLine));

		if (curLine.empty())
			continue;

		std::vector<std::string> tokens = SplitString(curLine, " ", false);

		if (tokens.size() < MAP_TOKENS_COUNT || tokens[0] != MAP_DATA_KEY)
			continue;

		const unsigned int width = std::stoul(tokens[MAP_WIDTH_INDEX]);
		const unsigned int height = std::stoul(tokens[MAP_HEIGHT_INDEX]);

		m_terrain.reserve(static_cast<size_t>(width) * height);

		bool isValidLine = true;

		for (unsigned int y = 0; y < height && isValidLine; y++)
		{
			if (!std::getline(fileStream, curLine))
			{
				isValidLine = false;
				break;
			}

			tokens = SplitString(curLine, " ", false);

			if (tokens.empty() || tokens.size() != width)
				return false;

			for (unsigned int x = 0; x < width; x++)
			{
				unsigned int terrainType = Unpack(std::stoul(tokens[x]),
					TERRAIN_TYPE_BIT_OFFSET, TERRAIN_TYPE_BIT_COUNT);

				m_terrain.push_back(static_cast<TerrainType>(terrainType));
			}
		}

		if (isValidLine)
			return true;
	}

	return false;
}

void TD::GameMap::Clear()
{
	m_width = 0;
	m_height = 0;
	m_terrain.clear();

	// TODO: When towers are implemented, deallocate them and clear m_towers
}
