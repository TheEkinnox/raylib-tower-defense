#pragma once
#include "HUDWindow.h"

namespace TD
{
	class IGameManager;
	class GameOverWindow : public HUDWindow
	{
	public:
		GameOverWindow(Vector2 position, Vector2 dimensions);
		~GameOverWindow() = default;

		void Create() override;
	};
}
