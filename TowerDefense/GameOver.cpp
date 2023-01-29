#include "pch.h"
#include "GameOver.h"
#include "TowerDefenseGameManager.h"
#include "Layer.h"
#include "ExitButton.h"
#include "PlayAgain.h"
#include "MainMenuButton.h"

namespace TD
{
	GameOverWindow::GameOverWindow(Vector2 position, Vector2 dimensions) : 
		HUDWindow(position, dimensions)
	{
	}


	void GameOverWindow::Create()
	{
		TowerDefenseGameManager& gameManager = TowerDefenseGameManager::GetInstance();
		const unsigned int money = gameManager.Player.Money;
		const unsigned int wave = gameManager.EnemyArmy.GetCurrentWave();
		Renderer& renderer = gameManager.GetRenderer();

		if (m_windowTexture.id == 0)
			throw;

		const int centerX = static_cast<int>(Dimensions.x / 2);
		const int centerY = static_cast<int>(Dimensions.y / 2);
		int textWidth = MeasureText(TITLE, FONT_SIZE_TITLE);
		char const* remainingMoneyText = TextFormat("Money remaining : %d", money);
		char const* waveText = TextFormat("Last reached wave : %d", wave);

		BeginTextureMode(m_windowTexture);

		ClearBackground(BLANK);

		DrawRectangleV({ 0, 0 }, Dimensions, COLOR_DARKENER);

		DrawText(TITLE, centerX - textWidth / 2, centerY - 125, FONT_SIZE_TITLE, COLOR_TITLE);

		textWidth = MeasureText(SUBTITLE, FONT_SIZE_CONTENT);
		DrawText(SUBTITLE, centerX - textWidth / 2, centerY - 115 + FONT_SIZE_TITLE, FONT_SIZE_CONTENT, COLOR_TITLE);

		textWidth = MeasureText(waveText, FONT_SIZE_CONTENT);
		DrawText(waveText, centerX - textWidth / 2, centerY, FONT_SIZE_CONTENT, LIGHTGRAY);

		textWidth = MeasureText(remainingMoneyText, FONT_SIZE_CONTENT);
		DrawText(remainingMoneyText, centerX - textWidth / 2, centerY-30, FONT_SIZE_CONTENT, GOLD);

		EndTextureMode();

		if (m_windowSprite == nullptr)
			m_windowSprite = &renderer.CreateSprite(m_windowTexture.texture, Position, Layer::WINDOW);
		else
			m_windowSprite->SetTexture(m_windowTexture.texture);

		m_windowSprite->SetScale(1, -1);
		m_windowSprite->SetOrigin(0, 0);

		AddButton<ExitButton>(Vector2{ Dimensions.x / 2 - 115, Dimensions.y / 2 + 80 });
		AddButton<PlayAgainButton>(Vector2{ Dimensions.x / 2 + 115, Dimensions.y / 2 + 80 });
		AddButton<MainMenuButton>(Vector2{ Dimensions.x / 2, Dimensions.y / 2 + 125 });
	}

	void GameOverWindow::Update()
	{
		if (TowerDefenseGameManager::GetInstance().GetCurrentState() != GameState::GAME_OVER)
			Close();
		else
			HUDWindow::Update();
	}
}