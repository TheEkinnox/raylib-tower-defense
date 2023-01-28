#include "pch.h"
#include "TowerButton.h"
#include "TowerDefenseGameManager.h"

namespace TD
{
	TowerButton::TowerButton(const Vector2 relativePosition, HUDWindow& window, const BulletType type) :
		HUDButton(relativePosition, window),
		m_isDragged(false), m_towerType(type)
	{
		m_towerConfig.LoadFromFile(type, 1);
	}

	void TowerButton::Update()
	{
		HUDButton::Update();
	}

	void TowerButton::Click()
	{
	}

	void TowerButton::DragAndDrop()
	{
		if (!m_isDragged && TowerDefenseGameManager::GetInstance().Player.Money >= m_towerConfig.price && IsHovered() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			m_isDragged = true;
			Sprite->Position() = GetMousePosition();
		}
		else if (m_isDragged && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			m_isDragged = false;
			// TODO: Check position and place new tower
			const Vector2 regularTowerPos = Vector2{Sprite->Position()};
			TowerDefenseGameManager::GetInstance().Player.Money - m_towerConfig.price;
		}
	}
}