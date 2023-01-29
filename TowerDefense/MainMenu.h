#pragma once
#include <string>
#include "HUDWindow.h"

namespace TD
{
	class MainMenu : public HUDWindow
	{
	public:
		MainMenu(const Vector2 position, const Vector2 dimensions);

		void		Create() override;
		void		Update();

	private:
		const char*			TITLE = "MAIN MENU";
		const char*			LOGO_PATH = "Assets/logo.png";
		const std::string	LEVELS_FOLDER = "Assets/maps";
		const char*			CONFIG_FILE_EXTENSION = ".cfg";
		const float			BUTTON_HEIGHT = 26;
	};
}
