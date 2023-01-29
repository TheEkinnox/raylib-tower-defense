#include "pch.h"
#include "TowerDefenseGameManager.h"

#include "utility.h"
#include "ExplosiveTower.h"
#include "RegularTower.h"
#include "StunTower.h"
#include "GameOver.h"
#include "InGameHUDWindow.h"
#include "PauseWindow.h"
#include "MainMenu.h"

namespace TD
{
	TowerDefenseGameManager::TowerDefenseGameManager() :
		IGameManager(), m_backgroundMusic()
	{
	}

	TowerDefenseGameManager::~TowerDefenseGameManager()
	{
		StopMusicStream(m_backgroundMusic);
		UnloadMusicStream(m_backgroundMusic);
	}

	void TowerDefenseGameManager::Init(const int argc, char* const* argv)
	{
		if (argc > 1)
			LoadLevel(TextFormat("Assets/maps/%s", argv[1]));
		else
			SetCurrentState(GameState::MAIN_MENU);

		m_backgroundMusic = LoadMusicStream("Assets/sounds/background_music.mp3");
		PlayMusicStream(m_backgroundMusic);
		SetMusicVolume(m_backgroundMusic, 0.5f);
	}

	void TowerDefenseGameManager::LoadLevel(const std::string configPath)
	{
		Map.Clear();
		EnemyArmy.ClearEnemies();

		if (!Map.BuildFromFile(configPath) ||
			!EnemyArmy.Load(configPath) ||
			!Player.Load(configPath))
		{
			SetCurrentState(GameState::ERROR);
		}

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

		if (IsKeyPressed(KEY_M))
			Player.AddMoney(INT_MAX);
	}
#endif

	void TowerDefenseGameManager::Update()
	{
		if (currentState == GameState::ERROR)
			return;

		if (!IsWindowFocused())
		{
			SetCurrentState(GameState::PAUSED);
			PauseMusicStream(m_backgroundMusic);
		}
		else
			PlayMusicStream(m_backgroundMusic);

		if (IsKeyPressed(KeyboardKey::KEY_F11))
			ToggleFullscreen();

		if (IsKeyPressed(KEY_ESCAPE))
			SetCurrentState(currentState == GameState::PAUSED ?
				GameState::RUNNING : GameState::PAUSED);

		try
		{
#ifdef _DEBUG
			HandleDevShortcuts();
#endif

			UpdateMusicStream(m_backgroundMusic);

			if (currentState == GameState::RUNNING)
			{
				EnemyArmy.Update();

				Map.UpdateTowers();
			}

			Player.Update();

			renderer.DrawSprites();
		}
		catch(std::exception& ex)
		{
			std::cout << "\n**ERROR: " << ex.what() << "**\n" << std::endl;
			SetCurrentState(GameState::ERROR);
		}
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
		{
			Map.Clear();
			EnemyArmy.ClearEnemies();
			Player.Clear();

			MainMenu* menu = new MainMenu({ 0, 0 }, renderer.GetRenderSize());
			menu->Create();

			Player.HUD.Windows.push_back(menu);
			break;
		}
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
			GameOverWindow* gameOver = new GameOverWindow({ 0, 0 }, renderer.GetRenderSize());
			gameOver->Create();

			Player.HUD.Windows.push_back(gameOver);
			break;
		}
		case GameState::QUIT:
			break;
		case GameState::ERROR:
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
