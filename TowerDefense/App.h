#pragma once
#include "AppConfig.h"

namespace TD
{
	class IGameManager;

	class App
	{
	public:
		App(int argc, char* const* argv);
		~App() = default;

		void			Run() const;

		static void		ToggleFullscreenWindow();
		static void		SetTimeScale(float timeScale);
		static float	GetScaledFrameTime();

	private:
		AppConfig		m_config;
		IGameManager*	m_gameManager;
		static float	m_timeScale;

		const char* CONFIG_FILE_PATH = "Assets/config.cfg";
	};
}
