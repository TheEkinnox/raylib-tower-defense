#pragma once
#include "HUDButton.h"

namespace TD
{
	class ExitButton : public HUDButton
	{
	public: 
		ExitButton(Vector2 relativePosition, HUDWindow& window);
		~ExitButton() = default;

		void	Click() override;
	};
}