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

		ButtonTexture = *renderer.GetTexture(m_towerConfig.buttonTexturePath);
		const Texture towerTexture = *renderer.GetTexture(m_towerConfig.texturePath);

		const Vector2 pos
		{
			m_window.Position.x + relativePosition.x,
			m_window.Position.y + relativePosition.y
		};

		Sprite = &renderer.CreateSprite(ButtonTexture, pos, Layer::BUTTON);
		m_towerSprite = &renderer.CreateSprite(towerTexture, Sprite->Position(), Layer::BUTTON);
		m_towerSprite->SetTint(BLANK);
	}

	TowerButton::~TowerButton()
	{
		HUDButton::~HUDButton();

		if (m_towerSprite != nullptr)
			TowerDefenseGameManager::GetInstance().GetRenderer().RemoveSprite(*m_towerSprite);
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
		const Player& player = TowerDefenseGameManager::GetInstance().Player;
		const GameMap& map = TowerDefenseGameManager::GetInstance().Map;

		if (m_isDragged)
		{
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				m_isDragged = false;
				m_towerSprite->SetTint(BLANK);
				BuyTower();
			}
			else
			{
				m_towerSprite->Position() = map.GetScreenPosition(map.GetMouseCellPosition());
			}
		}
		else if (player.Money >= m_towerConfig.price && IsHovered() &&
			IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			m_isDragged = true;
			m_towerSprite->Position() = map.GetScreenPosition(map.GetMouseCellPosition());
			m_towerSprite->SetTint(ColorAlpha(WHITE, .8f));
			m_towerSprite->SetScale(map.GetScale());
		}
	}
}