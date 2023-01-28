#include "pch.h"
#include "HUDButton.h"
#include "Sprite.h"
#include "TowerDefenseGameManager.h"
#include "HUDWindow.h"

namespace TD
{
	HUDButton::HUDButton(Vector2 relativePosition, HUDWindow& window) :
		Sprite(nullptr), ButtonTexture(), RelativePosition(relativePosition), m_window(window)
	{
		DefaultTint = WHITE;
		HoveredTint = GRAY;
		ClickedTint = DARKGRAY;
	}

	HUDButton::~HUDButton()
	{
		if (Sprite != nullptr)
			TowerDefenseGameManager::GetInstance().GetRenderer().RemoveSprite(*Sprite);
	}

	void HUDButton::Update()
	{
		if (IsHovered())
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
				Sprite->SetTint(ClickedTint);
			else
				Sprite->SetTint(HoveredTint);

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				Click();
		}
		else
			Sprite->SetTint(DefaultTint);
	}

	void HUDButton::Click()
	{
	}

	bool HUDButton::IsHovered()
	{
		const Vector2 pos = Sprite->Position();
		const Vector2 mousePos = GetMousePosition();
		const float width = static_cast<float>(Sprite->GetTexture().width);
		const float height = static_cast<float>(Sprite->GetTexture().height);

		return mousePos.x >= pos.x - width / 2 && mousePos.x <= pos.x + width / 2 &&
			mousePos.y >= pos.y - height / 2 && mousePos.y <= pos.y + height / 2;
	}
}