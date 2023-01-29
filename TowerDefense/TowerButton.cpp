#include "pch.h"
#include "TowerButton.h"
#include "TowerDefenseGameManager.h"
#include "HUDWindow.h"

namespace TD
{
	TowerButton::TowerButton(const Vector2 relativePosition, HUDWindow& window, const TowerType type) :
		HUDButton(relativePosition, window),
		m_isDragged(false), m_towerType(type)
	{
		m_towerConfig.LoadFromFile(type, 1);

		Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();

		switch (type)
		{
		case TowerType::REGULAR:
			ButtonTexture = *renderer.GetTexture("Assets/hud/PNG/regular_button.png");
			break;
		case TowerType::STUNNING:
			ButtonTexture = *renderer.GetTexture("Assets/hud/PNG/stun_button.png");
			break;
		case TowerType::EXPLOSIVE:
			ButtonTexture = *renderer.GetTexture("Assets/hud/PNG/explosive_button.png");
			break;
		default:
			break;
		}

		Vector2 pos
		{
			m_window.Position.x + relativePosition.x,
			m_window.Position.y + relativePosition.y
		};

		Sprite = &TowerDefenseGameManager::GetInstance().GetRenderer().CreateSprite(ButtonTexture, pos, Layer::BUTTON);
	}

	void TowerButton::Update()
	{
		HUDButton::Update();
		DragAndDrop();
	}

	void TowerButton::Click()
	{
	}

	void TowerButton::DragAndDrop()
	{
		Player& player = TowerDefenseGameManager::GetInstance().Player;
		if (!m_isDragged && player.Money >= m_towerConfig.price && IsHovered() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			m_isDragged = true;
			Sprite->Position() = GetMousePosition();
		}
		else if (m_isDragged && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			m_isDragged = false;
			// TODO: Check position and place new tower
			const Vector2 regularTowerPos = Vector2{Sprite->Position()};
			player.BuyTower(m_towerConfig);
		}
	}
}