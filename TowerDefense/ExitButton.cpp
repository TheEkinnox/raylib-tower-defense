#include "pch.h"
#include "ExitButton.h"
#include "TowerDefenseGameManager.h"
#include "HUDWindow.h"

namespace TD
{
	ExitButton::ExitButton(Vector2 relativePosition, HUDWindow& window) :
		HUDButton(relativePosition, window)
	{
		Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();
		ButtonTexture = *renderer.GetTexture("Assets/hud/PNG/exit_button.png");

		Vector2 pos
		{
			m_window.Position.x + relativePosition.x,
			m_window.Position.y + relativePosition.y
		};

		Sprite = &TowerDefenseGameManager::GetInstance().GetRenderer().CreateSprite(ButtonTexture, pos, Layer::BUTTON);
	}

	void ExitButton::Click()
	{
		TowerDefenseGameManager::GetInstance().SetCurrentState(GameState::QUIT);
	}
}