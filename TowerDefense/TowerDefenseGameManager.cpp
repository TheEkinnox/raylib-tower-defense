#include "pch.h"
#include "TowerDefenseGameManager.h"

#include "Sprite.h"
#include "utility.h"
#include "ExplosiveTower.h"
#include "RegularTower.h"

namespace TD
{

	TowerDefenseGameManager::TowerDefenseGameManager() : IGameManager()
	{
	}

	void TowerDefenseGameManager::Init()
	{
		//TODO: Handle this on level load - Init should just open the main menu
		if (!Map.BuildFromFile("Assets/maps/level2.cfg"))
		{
			currentState = GameState::ERROR;
			return;
		}

		const int pixelWidth = static_cast<int>(Map.GetWidth()) * TILE_WIDTH;
		const int pixelHeight = static_cast<int>(Map.GetHeight()) * TILE_HEIGHT;

		const RenderTexture mapTexture = LoadRenderTexture(pixelWidth, pixelHeight);

		if (mapTexture.id == 0)
		{
			currentState = GameState::ERROR;
			return;
		}

		BeginTextureMode(mapTexture);

			DrawTiles();

			DrawTextureV(*renderer.GetTexture("Assets/HQ.png"),
				Map.GetPlayerHQPosition(false), WHITE);

		EndTextureMode();

		const float		scale = Map.GetScale();

		const Vector2	pos = {
			0,
			0
		};

		Sprite& mapSprite = renderer.CreateSprite(mapTexture.texture, pos, 0);
		mapSprite.SetScale(scale, -scale);
	}

	void TowerDefenseGameManager::Update()
	{
		if (currentState == GameState::ERROR)
			return;

		if (IsKeyPressed(KeyboardKey::KEY_F11))
			ToggleFullscreen();

		if (IsKeyPressed(KEY_R))
		{
			Map.AddTower<ExplosiveTower>(Vector2{ (float)Random(0,Map.GetWidth() - 1), (float)Random(0, Map.GetHeight() - 1) });
			Map.AddTower<RegularTower>(Vector2{ (float)Random(0,Map.GetWidth() - 1), (float)Random(0, Map.GetHeight() - 1) });
		}

		EnemyArmy.Update();

		Map.UpdateTowers();

		renderer.DrawSprites();
	}

	TowerDefenseGameManager& TowerDefenseGameManager::GetInstance()
	{
		static TowerDefenseGameManager instance;
		return instance;
	}

	void TowerDefenseGameManager::DrawTiles()
	{
		const std::vector<TerrainType> tiles(Map.GetTiles());

		for (size_t i = 0; i < tiles.size(); i++)
		{
			const Vector2 pos{
				static_cast<float>(i % Map.GetWidth()) * TILE_WIDTH,
				static_cast<float>(i / Map.GetWidth()) * TILE_HEIGHT
			};

			switch (tiles[i])
			{
			case TerrainType::ROAD:
				DrawTextureV(*renderer.GetTexture("Assets/textures/PNG/Default size/towerDefense_tile034.png"), pos, WHITE);
				break;
			case TerrainType::DIRT:
				DrawTextureV(*renderer.GetTexture("Assets/textures/PNG/Default size/towerDefense_tile050.png"), pos, WHITE);
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
}
