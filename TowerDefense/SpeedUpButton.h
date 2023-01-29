#pragma once
#include "HUDButton.h"

namespace TD
{
	class SpeedUpButton : public HUDButton
	{
	public:
		SpeedUpButton(Vector2 relativePosition, HUDWindow& window);
		~SpeedUpButton() override;

		void	Click() override;
		void	Update() override;

	private:
		bool	isFaster;
	};
}
