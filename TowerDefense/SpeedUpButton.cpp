#include "pch.h"
#include "SpeedUpButton.h"

#include "App.h"
#include "HUDWindow.h"
#include "TowerDefenseGameManager.h"

namespace TD
{
	SpeedUpButton::SpeedUpButton(const Vector2 relativePosition, HUDWindow& window) :
		HUDButton(relativePosition, window), m_currentSpeed(GameSpeed::X1)
	{
		Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();
		ButtonTexture = *renderer.GetTexture("Assets/hud/PNG/button_speed_x1.png");
		m_x2Texture = *renderer.GetTexture("Assets/hud/PNG/button_speed_x2.png");
		m_x4Texture = *renderer.GetTexture("Assets/hud/PNG/button_speed_x4.png");

		const Vector2 pos
		{
			m_window.Position.x + relativePosition.x,
			m_window.Position.y + relativePosition.y
		};

		Sprite = &renderer.CreateSprite(ButtonTexture, pos, Layer::BUTTON);
	}

	SpeedUpButton::~SpeedUpButton()
	{
		App::SetTimeScale(1);
	}

	void SpeedUpButton::Click()
	{
		switch (m_currentSpeed)
		{
		case GameSpeed::X1:
			m_currentSpeed = GameSpeed::X2;
			Sprite->SetTexture(m_x2Texture);
			break;
		case GameSpeed::X2:
			m_currentSpeed = GameSpeed::X4;
			Sprite->SetTexture(m_x4Texture);
			break;
		case GameSpeed::X4:
			m_currentSpeed = GameSpeed::X1;
			Sprite->SetTexture(ButtonTexture);
			break;
		}

		App::SetTimeScale(static_cast<float>(m_currentSpeed));
	}

	void SpeedUpButton::Update()
	{
		HUDButton::Update();
	}
}
