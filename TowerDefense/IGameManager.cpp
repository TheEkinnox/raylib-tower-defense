#include "pch.h"
#include "IGameManager.h"

namespace TD
{
	Renderer& IGameManager::GetRenderer()
	{
		return renderer;
	}

	GameState IGameManager::GetCurrentState() const
	{
		return currentState;
	}

	void IGameManager::SetCurrentState(GameState state)
	{
		currentState = state;
	}

	IGameManager::IGameManager() : currentState(GameState::INIT)
	{
	}
}
