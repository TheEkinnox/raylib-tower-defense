#pragma once
#include <vector>

namespace TD
{
	class HUDWindow;

	class PlayerHUD
	{
	public:
		std::vector<HUDWindow*>	Windows;

		void					ClearWindows();
		void					Update();
	};
}