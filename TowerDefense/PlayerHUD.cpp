#include "pch.h"
#include "PlayerHUD.h"
#include "HUDWindow.h"

namespace TD
{
	PlayerHUD::~PlayerHUD()
	{
		ClearWindows();
	}

	void PlayerHUD::ClearWindows()
	{
		for (size_t i = 0; i < Windows.size(); i++)
			delete Windows[i];

		Windows.clear();
	}

	void PlayerHUD::Update()
	{
		for (size_t i = 0; i < Windows.size(); i++)
			Windows[i]->Update();
	}
}