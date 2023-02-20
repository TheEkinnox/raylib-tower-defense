#include "pch.h"
#include "AppConfig.h"

#include <fstream>

#include "utility.h"

namespace TD
{
	bool AppConfig::LoadFromFile(const std::string& path)
	{
		std::ifstream fileStream(path);

		if (!fileStream.is_open())
			return false;

		std::string curLine;
		bool isTitleLoaded = false;

		while (std::getline(fileStream, curLine))
		{
			curLine = Trim(RemoveComments(curLine));

			if (curLine.empty())
				continue;

			std::vector<std::string> tokens = SplitString(curLine, " ", false);

			if (tokens.size() < 2)
				continue;

			if (tokens[0] == "title")
			{
				title = TrimLeft(curLine.substr(tokens[0].size()));
				isTitleLoaded = true;
			}
			else if (tokens[0] == "design_width")
			{
				designWidth = std::stoi(tokens[1]);
			}
			else if (tokens[0] == "design_height")
			{
				designHeight = std::stoi(tokens[1]);
			}
			else if (tokens[0] == "min_width")
			{
				minWidth = std::stoi(tokens[1]);
			}
			else if (tokens[0] == "min_height")
			{
				minHeight = std::stoi(tokens[1]);
			}
		}

		return isTitleLoaded;
	}
}
