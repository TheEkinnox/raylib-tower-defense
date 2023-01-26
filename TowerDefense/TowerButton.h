#pragma once
#include "HUDButton.h"
#include "bulletType.h"
#include "ConfigTower.h"

namespace TD
{
	class TowerButton : public HUDButton
	{
	public:
		TowerButton(BulletType type, Texture defaultTexture, Texture hoveredTexture, Texture clickedTexture);
		~TowerButton() = default;

		void			Update() override;
		void			DragAndDrop();

	private:
		bool			m_isDragged;
		ConfigTower		m_towerConfig;
		BulletType		m_towerType;
	};
}