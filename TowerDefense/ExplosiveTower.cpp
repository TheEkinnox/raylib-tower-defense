#include "pch.h"
#include "ExplosiveTower.h"
#include "TowerDefenseGameManager.h"

namespace TD
{
	ExplosiveTower::ExplosiveTower(Vector2 position)
	{
		Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();
		const Texture* towerTexture = renderer.GetTexture("Assets/textures/PNG/Default size/towerDefense_tile270.png");
		m_sprite = &renderer.CreateSprite(*towerTexture, position, 1);

		GameMap& map = TowerDefenseGameManager::GetInstance().Map;
		const float scale = map.GetScale();
		m_sprite->SetScale(scale);
	}

	void ExplosiveTower::ShootAt()
	{
		Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();
		const Texture* towerTexture = renderer.GetTexture("Assets/textures/PNG/Default size/towerDefense_tile252.png");

		Sprite& bulletSprite = renderer.CreateSprite(*towerTexture, Position(), 2);

		m_bulletPool.GetObject(bulletSprite);
	};

	void ExplosiveTower::Update()
	{
		if (IsKeyPressed(KEY_E))
			ShootAt();

		m_bulletPool.Update();
	}
}