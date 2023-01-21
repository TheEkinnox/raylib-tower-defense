#include "pch.h"
#include <fstream>

#include "TowerDefenseGameManager.h"
#include "Arithmetic.h"
#include "GameMap.h"
#include "ITower.h"
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
			m_terrain.resize(static_cast<size_t>(width) * height, TerrainType::GRASS);
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

					const unsigned int tileData = std::stoul(tokens[x]);

					const Vector2 position = Vector2
					{
						static_cast<float>(x) * TILE_WIDTH,
						static_cast<float>(y) * TILE_HEIGHT
					};

					AddTile(tileData, static_cast<size_t>(y) * width + x);
					AddSpecialTile(tileData, position);
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

	ITower* GameMap::GetTowerOnScreenPosition(const Vector2 screenPos) const
	{
		const float scale = GetScale();
		const Vector2 cellPos{ screenPos.x / (TILE_WIDTH * scale), screenPos.y / (TILE_HEIGHT * scale) };
		const size_t index = static_cast<size_t>(cellPos.y) * GetWidth() + static_cast<size_t>(cellPos.x);

		if (index < 0 || index > m_towers.size())
			return nullptr;

		return m_towers[index];
	}

	void GameMap::UpdateTowers()
	{
		for (const auto tower : m_towers)
			if (tower != nullptr)
				tower->Update();
	}

	Vector2 GameMap::GetPlayerHQPosition() const
	{
		return m_hqPosition;
	}

	Vector2 GameMap::GetSpawnPosition() const
	{
		if (m_spawnPoints.empty())
			return { 0 , 0 };

		return m_spawnPoints[Random(0, static_cast<int>(m_spawnPoints.size()))];
	}

	void GameMap::Clear()
	{
		m_width = 0;
		m_height = 0;
		m_terrain.clear();

		for (const auto tower : m_towers)
			delete tower;

		m_towers.clear();
	}

	float GameMap::GetScale() const
	{
		Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();
		const int pixelWidth = static_cast<int>(GetWidth()) * TILE_WIDTH;
		const int pixelHeight = static_cast<int>(GetHeight()) * TILE_HEIGHT;
		const Vector2    scaleVec = renderer.GetTextureScale(pixelWidth, pixelHeight);

		return LibMath::min(scaleVec.x, scaleVec.y);
	}

	bool GameMap::AddTile(const unsigned int tileData, const size_t index)
	{
		try
		{
			const TerrainType type = static_cast<TerrainType>(Unpack(tileData,
				TERRAIN_TYPE_BIT_OFFSET, TERRAIN_TYPE_BIT_COUNT));

			m_terrain[index] = type;

			return true;
		}
		catch(...)
		{
			return false;
		}
	}

	bool GameMap::AddSpecialTile(const unsigned int tileData, const Vector2 position)
	{
		const SpecialType type = static_cast<SpecialType>(Unpack(tileData,
			SPECIAL_TYPE_BIT_OFFSET, SPECIAL_TYPE_BIT_COUNT));

		switch (type)
		{
		case SpecialType::NONE:
			break;
		case SpecialType::HQ:
			if (m_hqPosition.x != -1)
				return false;

			m_hqPosition = position;
			break;
		case SpecialType::SPAWN_POINT:
			m_spawnPoints.push_back(position);
			break;
		default:
			return false;
		}

		return true;
	}
}
