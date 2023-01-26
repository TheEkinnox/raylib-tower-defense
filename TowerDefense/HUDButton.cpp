#include "pch.h"
#include "HUDButton.h"
#include "Sprite.h"
#include "TowerDefenseGameManager.h"

namespace TD
{
	HUDButton::HUDButton(Texture defaultTexture, Texture hoveredTexture, Texture clickedTexture) : DefaultTexture(defaultTexture),
		HoveredTexture(hoveredTexture), ClickedTexture(clickedTexture)
	{
	}

	void HUDButton::Update()
	{
		if (IsHovered())
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
				Sprite->SetTexture(HoveredTexture);
			else
				Sprite->SetTexture(ClickedTexture);
		}
		else
			Sprite->SetTexture(DefaultTexture);
	}

	bool HUDButton::IsHovered()
	{
		const Vector2 pos = Sprite->Position();
		const Vector2 mousePos = GetMousePosition();
		const float width = Sprite->GetTexture().width;
		const float height = Sprite->GetTexture().height;

		return mousePos.x >= pos.x - width / 2 && mousePos.x <= pos.x + width / 2 &&
			mousePos.y >= pos.y - height / 2 && mousePos.y <= pos.y + height / 2;
	}
}