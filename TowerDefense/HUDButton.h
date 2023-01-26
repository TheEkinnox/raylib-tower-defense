#pragma once
#include <raylib.h>

#define HUD_LAYER 255

namespace TD
{
	class Sprite;

	class HUDButton
	{
	public:
		Sprite*			Sprite;
		Texture			DefaultTexture;
		Texture			HoveredTexture;
		Texture			ClickedTexture;
		Vector2			RelativePosition;

		HUDButton(Texture defaultTexture, Texture hoveredTexture, Texture clickedTexture);

		virtual void	Update();

	protected:
		bool			IsHovered();
	};
}