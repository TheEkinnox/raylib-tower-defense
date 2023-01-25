#include "pch.h"
#include <Vector/Vector2.h>
#include "TowerDefenseGameManager.h"
#include "RegularTower.h"
#include "ConfigTower.h"


namespace TD
{
	RegularTower::RegularTower(Vector2 position) : ITower()
	{
		if(!config.LoadFromFile(BulletType::REGULAR, level))
			throw;

		Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();
		const Texture* towerTexture = renderer.GetTexture("Assets/textures/PNG/Default size/towerDefense_tile249.png");
		m_sprite = &renderer.CreateSprite(*towerTexture, position, ENTITY_LAYER);
		
		GameMap& map = TowerDefenseGameManager::GetInstance().Map;
		const float scale = map.GetScale();
		m_sprite->SetScale(scale);
	}

	void RegularTower::LevelUp()
	{
		if (level == config.maxLevel)
			return;

		level++; // add payment here.

		if (!config.LoadFromFile(config.bulletType, level))
			throw;
	}

	void RegularTower::ShootAt(const Enemy& enemy)
	{
		if ( GetTime() < m_nextShootTime)
			return;

		Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();
		const Texture* bulletTexture = renderer.GetTexture("Assets/textures/PNG/Default size/towerDefense_tile275.png");
		Bullet& bullet = m_bulletPool.GetObject(renderer.CreateSprite(*bulletTexture, Position(), ENTITY_LAYER + 1), *this);

		LibMath::Vector2 dir(enemy.Position().x - Position().x, enemy.Position().y - Position().y);
		dir.normalize();

		bullet.dir = Vector2{ dir.m_x, dir.m_y };
		bullet.speed = config.bulletSpeed;

		m_nextShootTime = GetTime() + static_cast<double>(1 / config.firingRate);
	};

	void RegularTower::Update()
	{
		if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_R))
			LevelUp();

		Enemy* enemy = CheckRange();

		if (enemy != nullptr)
			ShootAt(*enemy);

		m_bulletPool.Update();
	}

	void RegularTower::OnBulletCollision(Enemy& enemy)
	{
		enemy.Damage(config.damage);
	}
}