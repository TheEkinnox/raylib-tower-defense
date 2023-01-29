#pragma once
#include "HUDButton.h"
#include "BulletType.h"
#include "ConfigTower.h"

namespace TD
{
	class TowerButton : public HUDButton
	{
	public:
		TowerButton(Vector2 relativePosition, HUDWindow& window, TowerType type);

		void			Update() override;
		void			Click() override;
		void			DragAndDrop();

	private:
		bool			m_isDragged;
		ConfigTower		m_towerConfig;
		TowerType		m_towerType;
	};
}