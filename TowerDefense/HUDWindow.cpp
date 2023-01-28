#include "pch.h"
#include "HUDWindow.h"
#include "HUDButton.h"
#include "TowerDefenseGameManager.h"

namespace TD
{
	HUDWindow::HUDWindow(const Vector2 position, const Vector2 dimensions) :
		Position(position), Dimensions(dimensions),
		m_windowTexture(LoadRenderTexture(static_cast<int>(dimensions.x),
			static_cast<int>(dimensions.y))), m_windowSprite(nullptr)
	{
	}

	HUDWindow::~HUDWindow()
	{
		Clear();
	}

	void HUDWindow::Update()
	{
		for (const auto& button : Buttons)
			if (button != nullptr)
				button->Update();
	}

	void HUDWindow::Clear()
	{
		for (const auto& button : Buttons)
			delete button;
		
		Buttons.clear();
		UnloadRenderTexture(m_windowTexture);

		if (m_windowSprite != nullptr)
		{
			Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();
			renderer.RemoveSprite(*m_windowSprite);
			m_windowSprite = nullptr;
		}
	}

	void HUDWindow::Close() const
	{
		TowerDefenseGameManager& gameManager = TowerDefenseGameManager::GetInstance();
		gameManager.Player.HUD.CloseWindow(this);
	}
}
