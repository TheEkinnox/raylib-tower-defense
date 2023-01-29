#pragma once
#include "HUDButton.h"
#include "BulletType.h"
#include "ConfigTower.h"

namespace TD
{
	class TowerButton : public HUDButton
	{
	public:
		void			Update() override;
		void			Click() override;

	protected:
		bool			m_isDragged;
		ConfigTower		m_towerConfig;
		TowerType		m_towerType;
		TD::Sprite*		m_towerSprite;

		TowerButton(Vector2 relativePosition, HUDWindow& window, TowerType type);
		~TowerButton() override;
		
		virtual void	BuyTower() = 0;

	private:
		void			DragAndDrop();
	};
}