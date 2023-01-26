#pragma once
#include <raylib.h>
#include <vector>

namespace TD
{
	class HUDButton;

	class HUDWindow
	{
	public:
		std::vector<HUDButton*>	Buttons;
		Vector2					Position;
		Vector2					Dimensions;

		template <typename T>
		T*						AddButton();

		void					Clear();
		virtual void			Create() = 0;
	};
}