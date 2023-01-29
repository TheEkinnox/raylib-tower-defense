#include "pch.h"
#include "TowerDefenseGameManager.h"

#include "utility.h"
#include "ExplosiveTower.h"
#include "RegularTower.h"
#include "StunTower.h"
#include "GameOver.h"
#include "InGameHUDWindow.h"
#include "PauseWindow.h"

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
		SetCurrentState(GameState::RUNNING);
	}

#ifdef _DEBUG
	void TowerDefenseGameManager::HandleDevShortcuts()
	{
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
			SetCurrentState(GameState::GAME_OVER);
	}
#endif

	void TowerDefenseGameManager::Update()
	{
		if (currentState == GameState::ERROR)
			return;

		if (!IsWindowFocused())
			SetCurrentState(GameState::PAUSED);

		if (IsKeyPressed(KeyboardKey::KEY_F11))
			ToggleFullscreen();

		if (IsKeyPressed(KEY_P))
			SetCurrentState(currentState == GameState::PAUSED ?
				GameState::RUNNING : GameState::PAUSED);

#ifdef _DEBUG
		HandleDevShortcuts();
#endif

		if (currentState == GameState::RUNNING)
		{
			EnemyArmy.Update();

			Map.UpdateTowers();
		}

		Player.Update();
		
		renderer.DrawSprites();
	}

	void TowerDefenseGameManager::SetCurrentState(const GameState state)
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
		{
			// Don't recreate the HUD if the game was just paused.
			// this UI doesn't get destroyed on pause
			if (currentState == GameState::PAUSED)
				break;

			const Vector2 inGameUIPos = { 0, renderer.GetRenderSize().y * .88f };
			const Vector2 inGameUISize = { renderer.GetRenderSize().x, renderer.GetRenderSize().y * .12f };
			InGameHUDWindow* inGameUI = new InGameHUDWindow(inGameUIPos, inGameUISize);
			inGameUI->Create();

			Player.HUD.Windows.push_back(inGameUI);
			break;
		}
		case GameState::PAUSED:
		{
			if (currentState != GameState::RUNNING)
				return;

			PauseWindow* pauseWindow = new PauseWindow({ 0, 0 }, renderer.GetRenderSize());
			pauseWindow->Create();

			Player.HUD.Windows.push_back(pauseWindow);
			break;
		}
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
			std::cout << "An unexpected error has occured." << std::endl;
			SetCurrentState(GameState::QUIT);
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
