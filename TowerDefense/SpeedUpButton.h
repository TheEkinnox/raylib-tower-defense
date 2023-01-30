#pragma once
#include "HUDButton.h"

namespace TD
{
	enum class GameSpeed
	{
		X1 = 1,
		X2 = 2,
		X4 = 4
	};

	class SpeedUpButton : public HUDButton
	{
	public:
		SpeedUpButton(Vector2 relativePosition, HUDWindow& window);
		~SpeedUpButton() override;

		void	Click() override;
		void	Update() override;

	private:
		Texture		m_x2Texture;
		Texture		m_x4Texture;
		GameSpeed	m_currentSpeed;
	};
}
