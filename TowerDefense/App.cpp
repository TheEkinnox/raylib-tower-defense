#include "pch.h"
#include <raylib.h>

#include "App.h"

#include <iostream>

#include "TowerDefenseGameManager.h"

namespace TD
{
	App::App() : m_gameManager(nullptr)
	{
	}

	void App::Init()
	{
        SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);

        // Set the working directory to avoid issues with asset paths
        ChangeDirectory(GetApplicationDirectory());

		InitWindow(App::designWidth, App::designHeight, "Tower Defense");
		SetWindowMinSize(App::minWidth, App::minHeight);
		InitAudioDevice();

		m_gameManager = &TowerDefenseGameManager::GetInstance();
		m_gameManager->Init();
	}

	void App::Run() const
	{
		while (!(WindowShouldClose() || m_gameManager->GetCurrentState() == GameState::QUIT || m_gameManager->GetCurrentState() == GameState::ERROR))
			m_gameManager->Update();
	}

	void App::Quit() const
	{
		CloseAudioDevice();
		CloseWindow();

		if (m_gameManager->GetCurrentState() == GameState::ERROR)
			std::cout << "\nAn unexpected error has occured..." << std::endl;
	}
}
