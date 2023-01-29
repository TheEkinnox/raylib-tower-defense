#pragma once
#include <string>
#include "HUDButton.h"


namespace TD
{
	class StartLevelButton : public HUDButton
	{
	public:
		StartLevelButton(Vector2 relativePosition, HUDWindow& window, const std::string& configPath);
		~StartLevelButton() override;

		void			Click() override;

	private:
		std::string		m_configPath;
		RenderTexture	m_renderTexture;

		const char*		FONT_PATH = "Assets/fonts/kenvector_future.ttf";
		const float		FONT_SIZE = 18;
		const float		TEXT_SPACING = 1;
	};
}