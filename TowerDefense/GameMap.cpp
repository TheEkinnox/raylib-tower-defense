#include "pch.h"
#include <fstream>

#include "GameMap.h"

#include "utility.h"

namespace TD
{
	GameMap::GameMap() : m_width(0), m_height(0)
	{
	}

	GameMap::~GameMap()
	{
		Clear();
	}

	unsigned int GameMap::GetWidth() const
	{
		return m_width;
	}

	unsigned int GameMap::GetHeight() const
	{
		return m_height;
	}

	std::vector<TerrainType> GameMap::GetTiles() const
	{
		return m_terrain;
	}

	bool GameMap::BuildFromFile(const std::string& fileName)
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

			m_terrain.clear();
			m_terrain.resize(static_cast<size_t>(width) * height, GRASS);
			m_terrain.shrink_to_fit();

			m_towers.clear();
			m_towers.resize(static_cast<size_t>(width) * height, nullptr);
			m_towers.shrink_to_fit();

			unsigned int y;

			for (y = 0; y < height && std::getline(fileStream, curLine); y++)
			{
				tokens = SplitString(curLine, " ", false);

				if (tokens.size() != width)
					return false;

				for (unsigned int x = 0; x < width; x++)
				{
					if (!std::isdigit(tokens[x][0]))
						return false;
					unsigned int tileData = std::stoul(tokens[x]);

					unsigned int terrainType = Unpack(tileData,
						TERRAIN_TYPE_BIT_OFFSET, TERRAIN_TYPE_BIT_COUNT);

					unsigned int specialType = static_cast<SpecialType>(Unpack(tileData,
						SPECIAL_TYPE_BIT_OFFSET, SPECIAL_TYPE_BIT_COUNT));

					switch (specialType)
					{
					case NONE:
						break;
					case HQ:
						if (m_hqPosition.x != -1)
							return false;

						m_hqPosition = Vector2{ static_cast<float>(x) * TILE_WIDTH, static_cast<float>(y) * TILE_HEIGHT };
						break;
					case SPAWN_POINT:
						// TODO: Handle spawn 
						break;
					default:
						return false;
					}

					size_t index = static_cast<size_t>(y) * width + x;

					m_terrain[index] = static_cast<TerrainType>(terrainType);
				}
			}

			if (y == height)
			{
				m_width = width;
				m_height = height;
				return true;
			}

			return false;
		}

		return false;
	}

	ITower* GameMap::GetTowerOnScreenPosition(Vector2 screenPos) const
	{
		Vector2 cellPos{ screenPos.x / TILE_WIDTH, screenPos.y / TILE_HEIGHT };
		size_t index = static_cast<size_t>(cellPos.y) * GetWidth() + static_cast<size_t>(cellPos.x);

		if (index < 0 || index > m_towers.size())
			return nullptr;

		return m_towers[index];
	}

	Vector2 GameMap::GetPlayerHQPosition() const
	{
		return m_hqPosition;
	}

	void GameMap::Clear()
	{
		m_width = 0;
		m_height = 0;
		m_terrain.clear();

		// TODO: When towers are implemented, deallocate them and clear m_towers
	}
}
