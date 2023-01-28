#include "pch.h"
#include "ResumeButton.h"

#include "HUDWindow.h"
#include "TowerDefenseGameManager.h"

namespace TD
{
	ResumeButton::ResumeButton(const Vector2 relativePosition, HUDWindow& window) :
		HUDButton(relativePosition, window)
	{
		Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();
		ButtonTexture = *renderer.GetTexture("Assets/hud/PNG/resume_button.png");

		const Vector2 pos
		{
			m_window.Position.x + relativePosition.x,
			m_window.Position.y + relativePosition.y
		};

		Sprite = &renderer.CreateSprite(ButtonTexture, pos, Layer::BUTTON);
	}

	void ResumeButton::Click()
	{
		TowerDefenseGameManager::GetInstance().SetCurrentState(GameState::RUNNING);
	}
}
