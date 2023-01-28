#include "pch.h"
#include "PlayAgain.h"
#include "TowerDefenseGameManager.h"
#include "HUDWindow.h"

namespace TD
{
	PlayAgainButton::PlayAgainButton(Vector2 relativePosition, HUDWindow& window) :
		HUDButton(relativePosition, window)
	{
		Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();
		ButtonTexture = *renderer.GetTexture("Assets/hud/PNG/play_again_button.png");

		Vector2 pos
		{
			m_window.Position.x + relativePosition.x,
			m_window.Position.y + relativePosition.y
		};

		Sprite = &TowerDefenseGameManager::GetInstance().GetRenderer().CreateSprite(ButtonTexture, pos, Layer::BUTTON);
	}

	void PlayAgainButton::Click()
	{
		TowerDefenseGameManager& gameManager = TowerDefenseGameManager::GetInstance();
		gameManager.LoadLevel(gameManager.GetCurrentLevel());
	}
}