#include "pch.h"
#include "PauseWindow.h"

#include "ExitButton.h"
#include "MainMenuButton.h"
#include "ResumeButton.h"
#include "TowerDefenseGameManager.h"

namespace TD
{
	PauseWindow::PauseWindow(const Vector2 position, const Vector2 dimensions) :
		HUDWindow(position, dimensions)
	{
	}

	void PauseWindow::Create()
	{
		TowerDefenseGameManager& gameManager = TowerDefenseGameManager::GetInstance();
		Renderer& renderer = gameManager.GetRenderer();

		if (m_windowTexture.id == 0)
			throw;

		const int centerX = static_cast<int>(Dimensions.x / 2);
		const int centerY = static_cast<int>(Dimensions.y / 2);
		const int textWidth = MeasureText(TITLE, FONT_SIZE_TITLE);

		BeginTextureMode(m_windowTexture);

		ClearBackground(BLANK);

		DrawRectangleV({0, 0}, Dimensions, COLOR_DARKENER);

		DrawText(TITLE, centerX - textWidth / 2, centerY - 150, FONT_SIZE_TITLE, COLOR_TITLE);

		EndTextureMode();

		if (m_windowSprite == nullptr)
			m_windowSprite = &renderer.CreateSprite(m_windowTexture.texture, Position, Layer::WINDOW);
		else
			m_windowSprite->SetTexture(m_windowTexture.texture);

		m_windowSprite->SetScale(1, -1);
		m_windowSprite->SetOrigin(0, 0);

		AddButton<ResumeButton>(Vector2{
			Dimensions.x / 2,
			Dimensions.y / 2 - 50
		});

		AddButton<MainMenuButton>(Vector2{
			Dimensions.x / 2,
			Dimensions.y / 2
		});

		AddButton<ExitButton>(Vector2{
			Dimensions.x / 2,
			Dimensions.y / 2 + 50
		});
	}

	void PauseWindow::Update()
	{
		if (TowerDefenseGameManager::GetInstance().GetCurrentState() != GameState::PAUSED)
			Close();
		else
			HUDWindow::Update();
	}
}
