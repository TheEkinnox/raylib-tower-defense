#include "pch.h"
#include "MainMenu.h"
#include "StartLevelButton.h"
#include "TowerDefenseGameManager.h"

namespace TD
{
	MainMenu::MainMenu(const Vector2 position, const Vector2 dimensions) :
		HUDWindow(position, dimensions)
	{
	}

	void MainMenu::Create()
	{
		TowerDefenseGameManager& gameManager = TowerDefenseGameManager::GetInstance();
		Renderer& renderer = gameManager.GetRenderer();

		if (m_windowTexture.id == 0)
			throw;

		FilePathList configFiles = LoadDirectoryFiles(LEVELS_FOLDER.c_str());

		if (configFiles.count == 0)
			throw;

		const int centerX = static_cast<int>(Dimensions.x / 2);
		const int centerY = static_cast<int>(Dimensions.y / 2);
		const Texture logoTexture = *renderer.GetTexture(LOGO_PATH);
		const float buttonsYOffset = logoTexture.height + 48;
		const float buttonAreaHeight = (Dimensions.y - buttonsYOffset - 16) * .8f;

		BeginTextureMode(m_windowTexture);

		ClearBackground(BLANK);

		DrawRectangleV({ 0, 0 }, Dimensions, COLOR_DARKENER);

		DrawTexture(logoTexture, centerX - logoTexture.width / 2, 32, WHITE);

		EndTextureMode();

		m_windowSprite = &renderer.CreateSprite(m_windowTexture.texture, Position, Layer::WINDOW);
		
		m_windowSprite->SetScale(1, -1);
		m_windowSprite->SetOrigin(0, 0);

		for (size_t i = 0; i < configFiles.count; i++)
		{
			const char* fileName = GetFileName(configFiles.paths[i]);
			
			if (!IsFileExtension(fileName, CONFIG_FILE_EXTENSION))
				continue;

			float yPos = buttonsYOffset + (i + 1) * buttonAreaHeight /
				(configFiles.count + 1) - BUTTON_HEIGHT / 2;

			const Vector2 btnPos
			{
				Dimensions.x / 2,
				yPos
			};

			const std::string configPath = LEVELS_FOLDER + '/' + fileName;
			AddButton<StartLevelButton>(btnPos, configPath);
		}
	}

	void MainMenu::Update()
	{
		if (TowerDefenseGameManager::GetInstance().GetCurrentState() != GameState::MAIN_MENU)
			Close();
		else
			HUDWindow::Update();
	}
}
