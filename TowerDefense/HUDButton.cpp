#include "pch.h"
#include "HUDButton.h"
#include "Sprite.h"
#include "TowerDefenseGameManager.h"
#include "HUDWindow.h"

namespace TD
{
	HUDButton::HUDButton(const Vector2 relativePosition, HUDWindow& window) :
		Sprite(nullptr), ButtonTexture(), DefaultTint(WHITE), HoveredTint(GRAY),
		ClickedTint(DARKGRAY), RelativePosition(relativePosition), m_window(window)
	{
	}

	HUDButton::~HUDButton()
	{
		if (Sprite != nullptr)
			TowerDefenseGameManager::GetInstance().GetRenderer().RemoveSprite(*Sprite);
	}

	void HUDButton::Update()
	{
		Sprite->Position() = Vector2{
			m_window.Position.x + RelativePosition.x,
			m_window.Position.y + RelativePosition.y
		};

		if (IsHovered())
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
				Sprite->SetTint(ClickedTint);
			else
				Sprite->SetTint(HoveredTint);

			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
				Click();
		}
		else
			Sprite->SetTint(DefaultTint);
	}

	bool HUDButton::IsHovered() const
	{
		const auto& state = TowerDefenseGameManager::GetInstance().GetCurrentState();
		const auto& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();
		const Vector2 scale = renderer.GetRenderScale();
		const Vector2 offset = renderer.GetRenderPosition();

		const Vector2 pos
		{
			Sprite->Position().x * scale.x + offset.x,
			Sprite->Position().y * scale.y + offset.y
		};

		const Vector2 mousePos = GetMousePosition();
		const float width = static_cast<float>(Sprite->GetTexture().width) * scale.x;
		const float height = static_cast<float>(Sprite->GetTexture().height) * scale.y;

		return mousePos.x >= pos.x - width / 2 && mousePos.x <= pos.x + width / 2 &&
			mousePos.y >= pos.y - height / 2 && mousePos.y <= pos.y + height / 2;
	}
}