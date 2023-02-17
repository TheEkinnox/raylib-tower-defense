#pragma once

namespace TD
{
	class IGameManager;

	class App
	{
	public:
		const int	DesignWidth = 1280;
		const int	DesignHeight = 654;

		const int	MinWidth = 800;
		const int	MinHeight = 360;

		App(int argc, char* const* argv);
		~App() = default;

		void			Run() const;

		static void		ToggleFullscreenWindow();
		static void		SetTimeScale(float timeScale);
		static float	GetScaledFrameTime();

	private:
		IGameManager*	m_gameManager;
		static float	m_timeScale;
	};
}
