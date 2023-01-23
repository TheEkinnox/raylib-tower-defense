#pragma once
#include <raylib.h>
#include <string>
#include <vector>
#include "ITower.h"

#define MAP_DATA_KEY "map"
#define MAP_TOKENS_COUNT 3
#define MAP_WIDTH_INDEX 1
#define MAP_HEIGHT_INDEX 2

#define TERRAIN_TYPE_BIT_OFFSET 3
#define TERRAIN_TYPE_BIT_COUNT 2

#define SPECIAL_TYPE_BIT_OFFSET TERRAIN_TYPE_BIT_OFFSET + TERRAIN_TYPE_BIT_COUNT
#define SPECIAL_TYPE_BIT_COUNT 2

#define TILE_WIDTH 64
#define TILE_HEIGHT 64

namespace TD
{
	enum class SpecialType
	{
		NONE,
		HQ,
		SPAWN_POINT
	};

	enum class TerrainType
	{
		ROAD,
		DIRT,
		GRASS,
		SAND
	};

	class ITower;

	class GameMap
	{
	public:
		GameMap();
		~GameMap();

		unsigned int				GetWidth() const;
		unsigned int				GetHeight() const;
		std::vector<TerrainType>	GetTiles() const;

		bool						BuildFromFile(const std::string& fileName);

		template<typename T>
		T*							AddTower(Vector2 cellPosition);
		ITower*						GetTowerOnScreenPosition(Vector2 screenPos) const;
		void						UpdateTowers() const;
		Vector2						GetPlayerHQPosition(bool scale = true) const;
		Vector2						GetSpawnPosition() const;
		float						GetScale() const;
		void						Clear();

	private:
		unsigned int				m_width;
		unsigned int				m_height;
		std::vector<TerrainType>	m_terrain;
		std::vector<ITower*>		m_towers;
		std::vector<Vector2>		m_spawnPoints;
		Vector2						m_hqPosition{ -1, -1 };

		bool						AddTile(unsigned int tileData, size_t index);
		bool						AddSpecialTile(unsigned int tileData, Vector2 position);
	};

	template<typename T>
	inline T* GameMap::AddTower(Vector2 cellPosition)
	{
		if (!std::is_base_of_v<ITower, T>)
			return nullptr;

		size_t index = static_cast<size_t>(cellPosition.y) * m_width + static_cast<size_t>(cellPosition.x);

		if (m_towers[index] != nullptr)
			return static_cast<T*>(m_towers[index]);

		const float scale = GetScale();

		Vector2 towerPos
		{
			cellPosition.x * TILE_WIDTH * scale,
			cellPosition.y * TILE_HEIGHT * scale
		};

		m_towers[index] = new T(towerPos);

		return static_cast<T*>(m_towers[index]);
	}
}
