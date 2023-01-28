#include "pch.h"
#include "TowerDefenseGameManager.h"

#include "Sprite.h"
#include "utility.h"
#include "ExplosiveTower.h"
#include "RegularTower.h"
#include "StunTower.h"
#include "GameOver.h"

namespace TD
{
	TowerDefenseGameManager::TowerDefenseGameManager() : IGameManager()
	{
	}

	void TowerDefenseGameManager::Init(const int argc, char* const* argv)
	{
		if (argc > 1)
			LoadLevel(TextFormat("Assets/maps/%s", argv[1]));
		else
			SetCurrentState(GameState::MAIN_MENU);
	}

	void TowerDefenseGameManager::LoadLevel(const std::string& configPath)
	{
		Map.Clear();
		EnemyArmy.ClearEnemies();
		Player.Clear();

		if (!Map.BuildFromFile(configPath) ||
			!EnemyArmy.Load(configPath) ||
			!Player.Load(configPath))
			currentState = GameState::ERROR;

		m_currentLevelPath = configPath;
		currentState = GameState::RUNNING;
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

		if (IsKeyPressed(KEY_G))
		{
			SetCurrentState(GameState::GAME_OVER);
		}

		EnemyArmy.Update();

		Map.UpdateTowers();

		Player.Update();
		
		renderer.DrawSprites();
	}

	void TowerDefenseGameManager::SetCurrentState(GameState state)
	{
		if (state == currentState)
			return;

		switch (state)
		{
		case GameState::INIT:
			break;
		case GameState::MAIN_MENU:
			break;
		case GameState::RUNNING:
			break;
		case GameState::GAME_OVER:
		{
			GameOverWindow* gameOver = new GameOverWindow({ 0, 0 }, renderer.GetRenderSize() );
			gameOver->Create();

			Player.HUD.Windows.push_back(gameOver);
			break;
		}
		case GameState::QUIT:
			break;
		case GameState::ERROR:
			break;
		default:
			break;
		}

		IGameManager::SetCurrentState(state);
	}

	std::string TowerDefenseGameManager::GetCurrentLevel() const
	{
		return m_currentLevelPath;
	}

	TowerDefenseGameManager& TowerDefenseGameManager::GetInstance()
	{
		static TowerDefenseGameManager instance;
		return instance;
	}
}
