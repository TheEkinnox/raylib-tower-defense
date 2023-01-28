#include "pch.h"
#include "MainMenuButton.h"

#include "HUDWindow.h"
#include "TowerDefenseGameManager.h"

namespace TD
{
	MainMenuButton::MainMenuButton(const Vector2 relativePosition, HUDWindow& window) :
		HUDButton(relativePosition, window)
	{
		Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();
		ButtonTexture = *renderer.GetTexture("Assets/hud/PNG/main_menu_button.png");

		const Vector2 pos
		{
			m_window.Position.x + relativePosition.x,
			m_window.Position.y + relativePosition.y
		};

		Sprite = &renderer.CreateSprite(ButtonTexture, pos, Layer::BUTTON);
	}

	void MainMenuButton::Click()
	{
		TowerDefenseGameManager::GetInstance().SetCurrentState(GameState::MAIN_MENU);
	}
}
