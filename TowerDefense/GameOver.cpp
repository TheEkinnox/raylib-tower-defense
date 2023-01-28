#include "pch.h"
#include "GameOver.h"
#include "TowerDefenseGameManager.h"
#include "Layer.h"
#include "ExitButton.h"
#include "PlayAgain.h"

namespace TD
{
	GameOverWindow::GameOverWindow(Vector2 position, Vector2 dimensions) : 
		HUDWindow(position, dimensions)
	{
	}

	void GameOverWindow::Create()
	{
		TowerDefenseGameManager& gameManager = TowerDefenseGameManager::GetInstance();
		unsigned int money = gameManager.Player.Money;
		Renderer& renderer = gameManager.GetRenderer();

		if (m_windowTexture.id == 0)
			throw;

		BeginTextureMode(m_windowTexture);

		DrawRectangleV(Position, Dimensions, ColorAlpha(DARKPURPLE, .7f));

		DrawText("GAME OVER !", Position.x + 500, Position.y + 200, 30, RED);
		DrawText("Your castle has been taken...", Position.x + 390, Position.y + 230, 30, RED);
		DrawText(TextFormat("Money remaining : %d", money), Position.x + 450, Position.y + 275, 30, ORANGE);
		//DrawText("Scored Time : %d" ,725,725,12,YELLOW);

		EndTextureMode();

		if (m_windowSprite == nullptr)
			m_windowSprite = &renderer.CreateSprite(m_windowTexture.texture, Position, Layer::WINDOW);
		else
			m_windowSprite->SetTexture(m_windowTexture.texture);

		m_windowSprite->SetScale(1, -1);
		m_windowSprite->SetOrigin(0, 0);

		AddButton<ExitButton>( Vector2 {500, 350});
		AddButton<PlayAgainButton>(Vector2{ 725, 350 });
	}
}