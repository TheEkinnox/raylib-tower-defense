#pragma once
#include "HUDWindow.h"

namespace TD
{
	class PauseWindow : public HUDWindow
	{
	public:
		PauseWindow(Vector2 position, Vector2 dimensions);

		void		Create() override;
		void		Update() override;

	private:
		const char*	TITLE = "PAUSE";
	};
}
