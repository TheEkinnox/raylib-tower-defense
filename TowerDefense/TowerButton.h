#pragma once
#include "HUDButton.h"
#include "bulletType.h"
#include "ConfigTower.h"

namespace TD
{
	class TowerButton : public HUDButton
	{
	public:
		TowerButton(Vector2 relativePosition, HUDWindow& window, BulletType type);

		void			Update() override;
		void			Click() override;
		void			DragAndDrop();

	private:
		bool			m_isDragged;
		ConfigTower		m_towerConfig;
		BulletType		m_towerType;
	};
}