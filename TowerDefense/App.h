#pragma once

namespace TD
{
	class IGameManager;

	class App
	{
	public:
		const int	designWidth = 1280;
		const int	designHeight = 720;

		const int	minWidth = 800;
		const int	minHeight = 600;

		App();
		~App() = default;

		void			Init();
		void			Run() const;
		void			Quit() const;

	private:
		IGameManager*	m_gameManager;
		//InputScanner	m_inputScanner; // TODO: uncomment this part when InputScanner is implemented
	};
}
