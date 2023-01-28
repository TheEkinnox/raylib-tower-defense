#pragma once
#include "HUDButton.h"

namespace TD
{
	class ResumeButton : public HUDButton
	{
	public:
		ResumeButton(Vector2 relativePosition, HUDWindow& window);

		void Click() override;
	};
}
