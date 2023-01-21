#include "pch.h"
#include "RegularTower.h"
#include "TowerDefenseGameManager.h"
#include "PooledObject.h"

namespace TD
{
	RegularTower::RegularTower(Vector2 position)
	{
		Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();
		const Texture* towerTexture = renderer.GetTexture("Assets/textures/PNG/Default size/towerDefense_tile271.png");
		m_sprite = &renderer.CreateSprite(*towerTexture, position, 1);

		GameMap& map = TowerDefenseGameManager::GetInstance().Map;
		const float scale = map.GetScale();
		m_sprite->SetScale(scale);
	}

	void RegularTower::ShootAt()
	{
		Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();
		const Texture* towerTexture = renderer.GetTexture("Assets/textures/PNG/Default size/towerDefense_tile275.png");

		m_bulletPool.GetObject(renderer.CreateSprite(*towerTexture, Position(), 2));
	};

	void RegularTower::Update()
	{
		if (IsKeyPressed(KEY_SPACE))
			ShootAt();

		m_bulletPool.Update();
	}
}