#include "pch.h"
#include "HUDWindow.h"
#include "HUDButton.h"
#include "TowerDefenseGameManager.h"

namespace TD
{
	HUDWindow::HUDWindow(Vector2 position, Vector2 dimensions) :
		Position(position), Dimensions(dimensions),
		m_windowTexture(LoadRenderTexture(dimensions.x, dimensions.y)),
		m_windowSprite(nullptr)
	{
	}

	HUDWindow::~HUDWindow()
	{
		Clear();
	}

	void HUDWindow::Update()
	{
		for (size_t i = 0; i < Buttons.size(); i++)
			Buttons[i]->Update();
	}

	void HUDWindow::Clear()
	{
		for (size_t i = 0; i < Buttons.size() ; i++)
			delete Buttons[i];
		
		Buttons.clear();
		UnloadRenderTexture(m_windowTexture);

		if (m_windowSprite != nullptr)
		{
			Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();
			renderer.RemoveSprite(*m_windowSprite);
			m_windowSprite = nullptr;
		}
	}
}