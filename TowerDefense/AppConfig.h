#pragma once
#include <string>

namespace TD
{
	struct AppConfig
	{
		std::string	title = "Tower Defense";
		int			designWidth = 1280;
		int			designHeight = 654;
		int			minWidth = 800;
		int			minHeight = 360;

		AppConfig() = default;
		~AppConfig() = default;

		bool		LoadFromFile(const std::string& path);
	};
}
