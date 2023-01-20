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

	IGameManager::IGameManager() : currentState(GameState::INIT)
	{
	}
}
