#include "pch.h"
#include <raylib.h>

#include "App.h"

#include <iostream>

#include "TowerDefenseGameManager.h"

namespace TD
{
	float App::m_timeScale = 1;

	App::App(const int argc, char* const* argv)
	{
		SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);

#ifdef _DEBUG
		ChangeDirectory(TextFormat("%s%s", GetApplicationDirectory(), "../../"));
#else
		// Set the working directory to avoid issues with asset paths
		ChangeDirectory(GetApplicationDirectory());
#endif

		m_config.LoadFromFile(CONFIG_FILE_PATH);

		InitWindow(m_config.designWidth, m_config.designHeight, m_config.title.c_str());
		SetWindowMinSize(m_config.minWidth, m_config.minHeight);
		InitAudioDevice();
		HideCursor();
		SetExitKey(KEY_NULL);

		m_gameManager = &TowerDefenseGameManager::GetInstance();
		m_gameManager->Init(argc, argv);
	}

	void App::Run() const
	{
		while (!(WindowShouldClose() || m_gameManager->GetCurrentState() == GameState::QUIT
			|| m_gameManager->GetCurrentState() == GameState::ERROR))
			m_gameManager->Update();

		CloseAudioDevice();
		CloseWindow();

		if (m_gameManager->GetCurrentState() == GameState::ERROR)
			std::cout << "\nAn unexpected error has occurred..." << std::endl;
	}

	void App::ToggleFullscreenWindow()
	{
		static int lastWidth, lastHeight;
		if (!IsWindowFullscreen())
		{
			lastWidth = GetScreenWidth();
			lastHeight = GetScreenHeight();

			const int monitor = GetCurrentMonitor();
			SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
			ToggleFullscreen();
		}
		else
		{
			ToggleFullscreen();
			SetWindowSize(lastWidth, lastHeight);
		}
	}

	void App::SetTimeScale(const float timeScale)
	{
		m_timeScale = timeScale;
	}

	float App::GetScaledFrameTime()
	{
		return GetFrameTime() * m_timeScale;
	}
}
