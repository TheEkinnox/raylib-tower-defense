#include "pch.h"
#include "StartLevelButton.h"
#include "TowerDefenseGameManager.h"
#include "HUDWindow.h"

namespace TD
{
	StartLevelButton::StartLevelButton(const Vector2 relativePosition, HUDWindow& window, const std::string& configPath) :
		HUDButton(relativePosition, window), m_configPath(configPath)
	{
		Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();
		ButtonTexture = *renderer.GetTexture("Assets/hud/PNG/button_default.png");
		m_renderTexture = LoadRenderTexture(ButtonTexture.width, ButtonTexture.height);

		Font font = LoadFont(FONT_PATH);
		std::string fileName = TextToPascal(GetFileNameWithoutExt(configPath.c_str()));
		const Vector2 textSize = MeasureTextEx(font, fileName.c_str(), FONT_SIZE, TEXT_SPACING);

		const Vector2 textPos
		{
			ButtonTexture.width / 2 - textSize.x / 2,
			ButtonTexture.height / 2 - textSize.y / 2
		};

		BeginTextureMode(m_renderTexture);

		ClearBackground(BLANK);

		DrawTexture(ButtonTexture, 0, 0, WHITE);
		DrawTextEx(font, fileName.c_str(), textPos, FONT_SIZE, TEXT_SPACING, BLACK);

		EndTextureMode();

		UnloadFont(font);

		const Vector2 pos
		{
			m_window.Position.x + relativePosition.x,
			m_window.Position.y + relativePosition.y
		};

		Sprite = &renderer.CreateSprite(m_renderTexture.texture, pos, Layer::BUTTON);
		Sprite->SetScale(1, -1);
	}

	StartLevelButton::~StartLevelButton()
	{
		HUDButton::~HUDButton();
		UnloadRenderTexture(m_renderTexture);
	}

	void StartLevelButton::Click()
	{
		TowerDefenseGameManager::GetInstance().LoadLevel(m_configPath);
	}
}
