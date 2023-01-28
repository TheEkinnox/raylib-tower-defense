#pragma once
#include "HUDButton.h"

namespace TD
{
	class PauseButton : public HUDButton
	{
	public:
		PauseButton(Vector2 relativePosition, HUDWindow& window);

		void	Click() override;
		void	Update() override;
	};
}
