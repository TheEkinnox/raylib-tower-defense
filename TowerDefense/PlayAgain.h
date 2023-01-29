#pragma once
#include "HUDButton.h"

namespace TD
{
	class PlayAgainButton : public HUDButton
	{
	public:
		PlayAgainButton(Vector2 relativePosition, HUDWindow& window);

		void	Click() override;
	};
}