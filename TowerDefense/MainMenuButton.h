#pragma once
#include "HUDButton.h"

namespace TD
{
	class MainMenuButton : public HUDButton
	{
	public:
		MainMenuButton(Vector2 relativePosition, HUDWindow& window);

		void	Click() override;
	};
}
