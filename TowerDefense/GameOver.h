#pragma once
#include "HUDWindow.h"

namespace TD
{
	class IGameManager;
	class GameOverWindow : public HUDWindow
	{
	public:
		GameOverWindow(Vector2 position, Vector2 dimensions);

		void		Create() override;

	private:
		const char* TITLE = "GAME OVER !";
		const char* SUBTITLE = "Your castle has been taken...";
	};
}
