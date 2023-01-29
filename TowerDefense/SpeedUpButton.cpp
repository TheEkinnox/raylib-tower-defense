#include "pch.h"
#include "SpeedUpButton.h"

#include "App.h"
#include "HUDWindow.h"
#include "TowerDefenseGameManager.h"

namespace TD
{
	SpeedUpButton::SpeedUpButton(const Vector2 relativePosition, HUDWindow& window) :
		HUDButton(relativePosition, window), isFaster(false)
	{
		Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();
		ButtonTexture = *renderer.GetTexture("Assets/hud/PNG/speed_up_button.png");

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
		isFaster = !isFaster;

		App::SetTimeScale(isFaster ? 2.f : 1.f);
	}

	void SpeedUpButton::Update()
	{
		HUDButton::Update();

		if (isFaster)
			Sprite->SetScale(-1, 1);
		else
			Sprite->SetScale(1, 1);
	}
}
