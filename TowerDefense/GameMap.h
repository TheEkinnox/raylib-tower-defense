#pragma once
#include <raylib.h>
#include <string>
#include <vector>

#define MAP_DATA_KEY "map"
#define MAP_TOKENS_COUNT 3
#define MAP_WIDTH_INDEX 1
#define MAP_HEIGHT_INDEX 2
#define TERRAIN_TYPE_BIT_OFFSET 3
#define TERRAIN_TYPE_BIT_COUNT 2

namespace TD
{
	enum TerrainType
	{
		ROAD,
		DIRT,
		GRASS,
		SAND
	};

	class GameMap
	{
	public:
		GameMap();
		~GameMap();

		bool						BuildFromFile(const std::string& fileName);

		template<typename T>
		T*							AddTower(Vector2 cellPosition);
		//ITower*						GetTowerOnScreenPosition(Vector2 screenPos); // TODO: Uncomment this when the towers are implemented
		Vector2						GetPlayerHQPosition() const;
		void						Clear();

	private:
		unsigned int				m_width;
		unsigned int				m_height;
		std::vector<TerrainType>	m_terrain;
		//std::vector<TD::ITower*>	m_towers; // TODO: Uncomment this when the towers are implemented
	};
}
