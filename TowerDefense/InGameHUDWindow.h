#pragma once
#include "HUDWindow.h"

namespace TD
{
	class InGameHUDWindow : public HUDWindow
	{
	public:
		InGameHUDWindow(Vector2 position, Vector2 dimensions);

		void		Create() override;
		void		Update() override;

	private:
		void		UpdateSprite();
	};
}
