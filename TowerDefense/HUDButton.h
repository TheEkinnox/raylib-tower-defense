#pragma once
#include <raylib.h>

#define HUD_LAYER 255

namespace TD
{
	class Sprite;
	class HUDWindow;
	class HUDButton
	{
	public:
		Sprite*			Sprite;
		Texture			ButtonTexture;
		Color			DefaultTint;
		Color			HoveredTint;
		Color			ClickedTint;
		Vector2			RelativePosition;

		HUDButton(Vector2 relativePosition, HUDWindow& window);
		~HUDButton();
		
		virtual void	Update();
		virtual void	Click();

	protected:
		HUDWindow&		m_window;
		bool			IsHovered();
	};
}