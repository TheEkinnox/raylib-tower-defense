#include "pch.h"
#include <fstream>

#include "TowerDefenseGameManager.h"
#include "Arithmetic.h"
#include "GameMap.h"
#include "ITower.h"
#include "utility.h"

namespace TD
{
	GameMap::GameMap() : m_width(0), m_height(0), m_mapTexture(), m_mapSprite(nullptr), m_graph(0)
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

	std::vector<TerrainTile> GameMap::GetTiles() const
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

		while (std::getline(fileStream, curLine))
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
			m_terrain.resize(static_cast<size_t>(width) * height);
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

					const uint8_t tileData = static_cast<uint8_t>(std::stoul(tokens[x]));

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
				return BuildGraph() && GenerateMapTexture();
			}

			return false;
		}

		return false;
	}

	ITower* GameMap::GetTowerOnScreenPosition(const Vector2 screenPos) const
	{
		const Vector2 cellPos = GetCellPosition(screenPos);
		const size_t index = PositionToIndex(cellPos);

		if (index < 0 || index > m_towers.size())
			return nullptr;

		return m_towers[index];
	}

	void GameMap::UpdateTowers() const
	{
		for (const auto tower : m_towers)
			if (tower != nullptr)
				tower->Update();
	}

	Vector2 GameMap::GetPlayerHQPosition(const bool scale) const
	{
		Vector2 pos = m_hqPosition;

		if (scale)
		{
			pos.x *= GetScale();
			pos.y *= GetScale();
		}

		return pos;
	}

	Vector2 GameMap::GetSpawnPosition(const Vector2 origin) const
	{
		if (m_spawnPoints.empty())
			return { 0 , 0 };

		const int index = Random(0, static_cast<int>(m_spawnPoints.size() - 1));
		Vector2 pos = m_spawnPoints[index];
		pos.x = (pos.x + TILE_WIDTH * origin.x) * GetScale();
		pos.y = (pos.y + TILE_HEIGHT * origin.y) * GetScale();

		return pos;
	}

	Vector2 GameMap::GetMouseCellPosition() const
	{
		const Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();

		const Vector2 mousePos = GetMousePosition();
		const Vector2 renderScale = renderer.GetRenderScale();
		const Vector2 renderPos = renderer.GetRenderPosition();
		
		const float xPos = (mousePos.x - renderPos.x) / renderScale.x;
		const float yPos = (mousePos.y - renderPos.y) / renderScale.y;

		return GetCellPosition(Vector2{ xPos, yPos });
	}

	Vector2 GameMap::GetCellPosition(const Vector2 screenPosition) const
	{
		const float scale = GetScale();

		return Vector2{
			LibMath::floor(screenPosition.x / (TILE_WIDTH * scale)),
			LibMath::floor(screenPosition.y / (TILE_HEIGHT * scale))
		};
	}

	Vector2 GameMap::GetScreenPosition(const Vector2 cellPosition,
		const Vector2 origin, const bool useScale) const
	{
		const float scale = useScale ? GetScale() : 1;
		const float xOffset = TILE_WIDTH * origin.x * scale;
		const float yOffset = TILE_HEIGHT * origin.y * scale;

		return Vector2{
				cellPosition.x * TILE_WIDTH * scale + xOffset,
				cellPosition.y * TILE_HEIGHT * scale + yOffset
		};
	}

	unsigned int GameMap::PositionToIndex(const Vector2 cellPosition) const
	{
		return static_cast<unsigned int>(cellPosition.y) * GetWidth() +
			static_cast<unsigned int>(cellPosition.x);
	}

	Vector2 GameMap::IndexToPosition(const uint32_t index) const
	{
		return Vector2{
				static_cast<float>(index % m_width),
				static_cast<float>(index / m_width)
		};
	}

	float GameMap::GetScale() const
	{
		const Renderer&	renderer = TowerDefenseGameManager::GetInstance().GetRenderer();
		const float		pixelWidth = static_cast<float>(GetWidth()) * TILE_WIDTH;
		const float		pixelHeight = static_cast<float>(GetHeight()) * TILE_HEIGHT;
		const Vector2	scaleVec = renderer.GetTextureScale(pixelWidth, pixelHeight, { 1, .88f });

		return LibMath::min(scaleVec.x, scaleVec.y);
	}

	ai::Graph GameMap::GetGraph() const
	{
		return m_graph;
	}

	Texture GameMap::GetTexture() const
	{
		return m_mapTexture.texture;
	}

	void GameMap::Clear()
	{
		m_width = 0;
		m_height = 0;
		m_terrain.clear();

		for (const auto tower : m_towers)
			delete tower;

		m_towers.clear();
		m_spawnPoints.clear();
		m_hqPosition = { -1, -1 };

		if (m_mapSprite != nullptr)
		{
			Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();
			renderer.RemoveSprite(*m_mapSprite);
			m_mapSprite = nullptr;
		}

		UnloadRenderTexture(m_mapTexture);
		m_mapTexture.id = 0;
	}

	bool GameMap::AddTile(const uint8_t tileData, const size_t index)
	{
		try
		{
			const TerrainType type = static_cast<TerrainType>(Unpack(tileData,
				TERRAIN_TYPE_BIT_OFFSET, TERRAIN_TYPE_BIT_COUNT));

			m_terrain[index] = { type, static_cast<uint32_t>(type) << TILE_WEIGHT_OFFSET};

			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	bool GameMap::AddSpecialTile(const uint8_t tileData, const Vector2 position)
	{
		const SpecialType type = static_cast<SpecialType>(Unpack(tileData,
			SPECIAL_TYPE_BIT_OFFSET, SPECIAL_TYPE_BIT_COUNT));

		switch (type)
		{
		case SpecialType::NONE:
			break;
		case SpecialType::HQ:
			if (m_hqPosition.x >= 0)
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

	bool GameMap::BuildGraph()
	{
		if (m_terrain.empty())
			return false;

		ai::Graph graph(static_cast<unsigned int>(m_terrain.size()));

		for (unsigned int i = 0; i < m_terrain.size(); i++)
		{
			const Vector2 cellPos = IndexToPosition(i);

			ai::Node& node = *graph.GetNode(i);
			unsigned int neighborIndex;

			// Try to link up tile
			if (cellPos.y > 0)
			{
				neighborIndex = PositionToIndex({ cellPos.x, cellPos.y - 1 });
				node.AddEdge(graph.GetNode(neighborIndex),
					m_terrain[neighborIndex].Weight);
			}

			// Try to link down tile
			if (static_cast<unsigned int>(cellPos.y) < m_height - 1)
			{
				neighborIndex = PositionToIndex({ cellPos.x, cellPos.y + 1 });
				node.AddEdge(graph.GetNode(neighborIndex),
					m_terrain[neighborIndex].Weight);
			}

			// Try to link left tile
			if (cellPos.x > 0)
			{
				neighborIndex = PositionToIndex({ cellPos.x - 1, cellPos.y });
				node.AddEdge(graph.GetNode(neighborIndex),
					m_terrain[neighborIndex].Weight);
			}

			// Try to link right tile
			if (static_cast<unsigned int>(cellPos.x) < m_width - 1)
			{
				neighborIndex = PositionToIndex({ cellPos.x + 1, cellPos.y });
				node.AddEdge(graph.GetNode(neighborIndex),
					m_terrain[neighborIndex].Weight);
			}
		}

		m_graph = std::move(graph);

		return true;
	}

	bool GameMap::GenerateMapTexture()
	{
		const int pixelWidth = static_cast<int>(m_width) * TILE_WIDTH;
		const int pixelHeight = static_cast<int>(m_height) * TILE_HEIGHT;

		Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();

		m_mapTexture = LoadRenderTexture(pixelWidth, pixelHeight);

		if (m_mapTexture.id == 0)
			return false;

		BeginTextureMode(m_mapTexture);

		ClearBackground(BLANK);

		DrawTiles();

		DrawSpawnPoints();

		DrawTextureV(*renderer.GetTexture("Assets/HQ.png"),
			GetPlayerHQPosition(false), WHITE);

		EndTextureMode();

		const Vector2 pos = {
			static_cast<float>(m_mapTexture.texture.width) / 2,
			static_cast<float>(m_mapTexture.texture.height) / 2
		};

		if (m_mapSprite == nullptr)
			m_mapSprite = &renderer.CreateSprite(m_mapTexture.texture, pos, Layer::MAP);
		else
			m_mapSprite->SetTexture(m_mapTexture.texture);

		const float scale = GetScale();
		m_mapSprite->SetScale(scale, -scale);

		return true;
	}

	void GameMap::DrawTiles() const
	{
		Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();
		for (size_t i = 0; i < m_terrain.size(); i++)
		{
			const Vector2 cellPos = IndexToPosition(static_cast<uint32_t>(i));
			const Vector2 pos = GetScreenPosition(cellPos, { 0, 0 }, false);

			switch (m_terrain[i].Type)
			{
			case TerrainType::ROAD:
				DrawTextureV(*renderer.GetTexture("Assets/textures/PNG/Default size/towerDefense_tile034.png"), pos, WHITE);
				break;
			case TerrainType::DIRT:
				DrawTextureV(*renderer.GetTexture("Assets/textures/PNG/Default size/towerDefense_tile093.png"), pos, WHITE);
				break;
			case TerrainType::GRASS:
				DrawTextureV(*renderer.GetTexture("Assets/textures/PNG/Default size/towerDefense_tile024.png"), pos, WHITE);
				break;
			case TerrainType::SAND:
				DrawTextureV(*renderer.GetTexture("Assets/textures/PNG/Default size/towerDefense_tile029.png"), pos, WHITE);
				break;
			}
		}
	}
	
	void GameMap::DrawSpawnPoints() const
	{
		Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();

		for (size_t i = 0; i < m_spawnPoints.size(); i++)
		{
			const Vector2 cellPos
			{
				m_spawnPoints[i].x / TILE_WIDTH,
				m_spawnPoints[i].y / TILE_HEIGHT
			};
			const Vector2 pos = GetScreenPosition(cellPos, { 0, 0 }, false);

			DrawTextureV(*renderer.GetTexture("Assets/textures/PNG/Default size/towerDefense_tile022.png"), pos, WHITE);
		}
	}
}
