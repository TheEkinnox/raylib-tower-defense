#pragma once
#include "Renderer.h"

namespace TD
{
	enum class GameState
	{
		INIT,
		MAIN_MENU,
		RUNNING,
		GAME_OVER,
		QUIT,
		ERROR
	};

	class IGameManager
	{
	public:
		virtual				~IGameManager() = default;

		virtual void		Init() = 0;
		virtual void		Update() = 0;

		Renderer&			GetRenderer();
		GameState			GetCurrentState() const;

	protected:
		IGameManager();

		Renderer		renderer;
		GameState		currentState;
	};
}
