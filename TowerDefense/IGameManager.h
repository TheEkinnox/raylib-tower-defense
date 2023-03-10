#pragma once
#include "Renderer.h"

namespace TD
{
	enum class GameState
	{
		INIT,
		MAIN_MENU,
		RUNNING,
		PAUSED,
		GAME_OVER,
		QUIT,
		ERROR
	};

	class IGameManager
	{
	public:
		virtual				~IGameManager() = default;

		virtual void		Init(int argc = 0, char* const* argv = nullptr) = 0;
		virtual void		Update() = 0;

		Renderer&			GetRenderer();
		GameState			GetCurrentState() const;
		virtual void		SetCurrentState(GameState state);
		

	protected:
		IGameManager();

		Renderer		renderer;
		GameState		currentState;
	};
}
