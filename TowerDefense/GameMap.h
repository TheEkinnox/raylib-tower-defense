#pragma once
#include <raylib.h>
#include <string>
#include <vector>
#include "ITower.h"
#include "Graph.h"

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
#define TILE_WEIGHT_OFFSET 7

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

	struct TerrainTile
	{
		TerrainType		Type = TerrainType::GRASS;
		unsigned int	Weight = static_cast<uint32_t>(TerrainType::GRASS) << TERRAIN_TYPE_BIT_OFFSET;
	};

	class GameMap
	{
	public:
		GameMap();
		~GameMap();

		unsigned int				GetWidth() const;
		unsigned int				GetHeight() const;
		std::vector<TerrainTile>	GetTiles() const;

		bool						BuildFromFile(const std::string& fileName);

		template<typename T>
		T*							AddTower(Vector2 cellPosition);
		ITower*						GetTowerOnScreenPosition(Vector2 screenPos) const;
		void						UpdateTowers() const;
		Vector2						GetPlayerHQPosition(bool scale = true) const;
		Vector2						GetSpawnPosition(Vector2 origin = { .5f, .5f }) const;
		Vector2 GetMouseCellPosition() const;
		Vector2						GetCellPosition(Vector2 screenPosition) const;
		Vector2						GetScreenPosition(Vector2 cellPosition, Vector2 origin = { .5f, .5f }, bool useScale = true) const;
		Vector2						IndexToPosition(uint32_t index) const;
		unsigned int				PositionToIndex(Vector2 cellPosition) const;
		float						GetScale() const;
		ai::Graph					GetGraph() const;
		Texture						GetTexture() const;
		void						Clear();

	private:
		unsigned int				m_width;
		unsigned int				m_height;
		std::vector<TerrainTile>	m_terrain;
		std::vector<ITower*>		m_towers;
		std::vector<Vector2>		m_spawnPoints;
		RenderTexture				m_mapTexture;
		Sprite*						m_mapSprite;
		Vector2						m_hqPosition{ -1, -1 };
		ai::Graph					m_graph;

		bool						AddTile(uint8_t tileData, size_t index);
		bool						AddSpecialTile(uint8_t tileData, Vector2 position);
		bool						BuildGraph();
		bool						GenerateMapTexture();
		void						DrawTiles() const;
	};

	template<typename T>
	T* GameMap::AddTower(const Vector2 cellPosition)
	{
		if (!std::is_base_of_v<ITower, T>)
			return nullptr;

		const unsigned int index = PositionToIndex(cellPosition);

		if (index > m_towers.size() || m_towers[index] != nullptr
			|| m_terrain[index].Type == TerrainType::ROAD
			|| m_terrain[index].Type == TerrainType::DIRT)
			return nullptr;

		Vector2 towerPos = GetScreenPosition(cellPosition);

		m_towers[index] = new T(towerPos);

		return static_cast<T*>(m_towers[index]);
	}
}
