#include "pch.h"
#include "TowerDefenseGameManager.h"

#include "Sprite.h"
#include "utility.h"
#include "ExplosiveTower.h"
#include "RegularTower.h"
#include "StunTower.h"

namespace TD
{

	TowerDefenseGameManager::TowerDefenseGameManager() : IGameManager()
	{
	}

	void TowerDefenseGameManager::Init(const int argc, char* const* argv)
	{
		const char* configPath = TextFormat("Assets/maps/%s",
			argc > 1 ? argv[1] : "level1.cfg");

		//TODO: Handle this on level load - Init should just open the main menu
		if (!Map.BuildFromFile(configPath))
			currentState = GameState::ERROR;

		const float scale = Map.GetScale();
		const Texture mapTexture = Map.GetTexture();

		const Vector2 pos = {
			static_cast<float>(mapTexture.width) / 2,
			static_cast<float>(mapTexture.height) / 2
		};

		Sprite& mapSprite = renderer.CreateSprite(mapTexture, pos, 0);
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
			const Vector2 regularTowerPos = Vector2{
				static_cast<float>(Random(0, static_cast<int>(Map.GetWidth()) - 1)),
				static_cast<float>(Random(0, static_cast<int>(Map.GetHeight()) - 1))
			};
			Map.AddTower<RegularTower>(regularTowerPos);
		}

		if (IsKeyPressed(KEY_S))
		{

			const Vector2 stunTowerPos = Vector2{
				static_cast<float>(Random(0, static_cast<int>(Map.GetWidth()) - 1)),
				static_cast<float>(Random(0, static_cast<int>(Map.GetHeight()) - 1))
			};
			Map.AddTower<StunTower>(stunTowerPos);
		}

		if (IsKeyPressed(KEY_E))
		{
			const Vector2 explosiveTowerPos = Vector2{
				static_cast<float>(Random(0, static_cast<int>(Map.GetWidth()) - 1)),
				static_cast<float>(Random(0, static_cast<int>(Map.GetHeight()) - 1))
			};
			Map.AddTower<ExplosiveTower>(explosiveTowerPos);
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
}
