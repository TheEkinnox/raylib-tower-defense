#include "pch.h"
#include "PauseButton.h"

#include "HUDWindow.h"
#include "TowerDefenseGameManager.h"

namespace TD
{
	PauseButton::PauseButton(const Vector2 relativePosition, HUDWindow& window) :
		HUDButton(relativePosition, window)
	{
		Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();
		ButtonTexture = *renderer.GetTexture("Assets/hud/PNG/pause_button.png");

		const Vector2 pos
		{
			m_window.Position.x + relativePosition.x,
			m_window.Position.y + relativePosition.y
		};

		Sprite = &renderer.CreateSprite(ButtonTexture, pos, Layer::BUTTON);
	}

	void PauseButton::Click()
	{
		TowerDefenseGameManager::GetInstance().SetCurrentState(GameState::PAUSED);
	}

	void PauseButton::Update()
	{
		const GameState gameState = TowerDefenseGameManager::GetInstance().GetCurrentState();
		if (gameState != GameState::PAUSED)
		{
			Sprite->SetScale(1);
			HUDButton::Update();
		}
		else
		{
			Sprite->SetScale(0);
		}
	}
}
