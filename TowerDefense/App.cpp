#include "pch.h"
#include <raylib.h>

#include "App.h"

#include <iostream>

#include "TowerDefenseGameManager.h"

namespace TD
{
	float App::m_timeScale = 1;

	App::App() : m_gameManager(nullptr)
	{
	}

	void App::Init(const int argc, char* const* argv)
	{
		SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);

#ifdef _DEBUG
		ChangeDirectory(TextFormat("%s%s", GetApplicationDirectory(), "../../"));
#else
		// Set the working directory to avoid issues with asset paths
		ChangeDirectory(GetApplicationDirectory());
#endif

		InitWindow(App::DesignWidth, App::DesignHeight, "Tower Defense");
		SetWindowMinSize(App::MinWidth, App::MinHeight);
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
	}

	void App::Quit() const
	{
		CloseAudioDevice();
		CloseWindow();

		if (m_gameManager->GetCurrentState() == GameState::ERROR)
			std::cout << "\nAn unexpected error has occured..." << std::endl;
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
