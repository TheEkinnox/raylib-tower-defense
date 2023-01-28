#pragma once
#include <vector>

namespace TD
{
	class HUDWindow;

	class PlayerHUD
	{
	public:
		PlayerHUD() = default;
		~PlayerHUD();

		std::vector<HUDWindow*>	Windows;

		void					ClearWindows();
		void					Update();
	};
}