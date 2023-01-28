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
			if (Windows[i] != nullptr)
				delete Windows[i];

		Windows.clear();
	}

	void PlayerHUD::CloseWindow(const HUDWindow* window)
	{
		if (window == nullptr)
			return;

		auto isTarget = [window](const HUDWindow* other)
		{
			return other == window;
		};

		const auto toClose = std::find_if(Windows.begin(), Windows.end(), isTarget);

		if (toClose != Windows.end())
		{
			Windows.erase(toClose);
			delete window;
		}
	}

	void PlayerHUD::Update()
	{
		for (size_t i = 0; i < Windows.size(); i++)
			if (Windows[i] != nullptr)
				Windows[i]->Update();
	}
}