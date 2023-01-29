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

		App();
		~App() = default;

		void			Init(int argc = 0, char* const* argv = nullptr);
		void			Run() const;
		void			Quit() const;

		static void		SetTimeScale(float timeScale);
		static float	GetScaledFrameTime();

	private:
		IGameManager*	m_gameManager;
		static float	m_timeScale;
	};
}
