#include "pch.h"
#include "InGameHUDWindow.h"

#include "ExplosiveTowerButton.h"
#include "TowerButton.h"
#include "PauseButton.h"
#include "RegularTowerButton.h"
#include "StunTowerButton.h"
#include "TowerDefenseGameManager.h"

namespace TD
{
	InGameHUDWindow::InGameHUDWindow(const Vector2 position, const Vector2 dimensions) :
		HUDWindow(position, dimensions)
	{
	}

	void InGameHUDWindow::Create()
	{
		if (m_windowTexture.id == 0)
			throw;

		UpdateSprite();

		m_windowSprite->SetScale(1, -1);
		m_windowSprite->SetOrigin(0, 0);

		AddButton<RegularTowerButton>({Dimensions.x/2 - 150, Dimensions.y/2});
		AddButton<StunTowerButton>({Dimensions.x / 2, Dimensions.y / 2 });
		AddButton<ExplosiveTowerButton>({Dimensions.x / 2 + 150, Dimensions.y / 2 });

		AddButton<PauseButton>(Vector2{
			Dimensions.x - 32,
			Dimensions.y / 2
		});
	}

	void InGameHUDWindow::Update()
	{
		const GameState gameState = TowerDefenseGameManager::GetInstance().GetCurrentState();
		if (gameState != GameState::RUNNING && gameState != GameState::PAUSED)
			Close();
		else
		{
			UpdateSprite();
			HUDWindow::Update();
		}
	}

	void InGameHUDWindow::UpdateSprite()
	{
		TowerDefenseGameManager& gameManager = TowerDefenseGameManager::GetInstance();
		Renderer& renderer = gameManager.GetRenderer();
		const int centerY = static_cast<int>(Dimensions.y) / 2;

		const unsigned int wave = gameManager.EnemyArmy.GetCurrentWave();
		const unsigned int health = gameManager.Player.BaseHealth;
		const unsigned int money = gameManager.Player.Money;

		const char* waveText = TextFormat("Wave %u", wave);
		const char* moneyText = TextFormat("%u Gold", money);
		const char* healthText = TextFormat("%u HP", health);

		BeginTextureMode(m_windowTexture);

		ClearBackground(BLANK);

		DrawRectangleV({ 0, 0 }, Dimensions, COLOR_DARKENER);

		int xPos = 32;
		DrawText(waveText, xPos, centerY - FONT_SIZE_CONTENT / 3, FONT_SIZE_CONTENT, RAYWHITE);

		xPos += MeasureText(waveText, FONT_SIZE_CONTENT) + 32;
		DrawText(healthText, xPos, centerY - FONT_SIZE_CONTENT / 3, FONT_SIZE_CONTENT, RED);

		xPos += MeasureText(healthText, FONT_SIZE_CONTENT) + 32;
		DrawText(moneyText, xPos, centerY - FONT_SIZE_CONTENT / 3, FONT_SIZE_CONTENT, GOLD);

		EndTextureMode();

		if (m_windowSprite == nullptr)
			m_windowSprite = &renderer.CreateSprite(m_windowTexture.texture, Position, Layer::WINDOW);
		else
			m_windowSprite->SetTexture(m_windowTexture.texture);
	}
}
