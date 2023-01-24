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
		const Texture* towerTexture = renderer.GetTexture("Assets/textures/PNG/Default size/towerDefense_tile271.png");
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

		const float scale = TowerDefenseGameManager::GetInstance().Map.GetScale();
		const float scaledWidth = static_cast<float>(m_sprite->GetTexture().width) * scale;
		const float scaledHeight = static_cast<float>(m_sprite->GetTexture().height) * scale;

		const Vector2 spawnPos = {
			Position().x + scaledWidth / 2,
			Position().y + scaledHeight / 2,
		};

		Bullet& bullet = m_bulletPool.GetObject(renderer.CreateSprite(*bulletTexture, spawnPos, ENTITY_LAYER + 1));

		LibMath::Vector2 dir(enemy.Position().x - Position().x, enemy.Position().y - Position().y);
		dir.normalize();

		bullet.dir = Vector2{ dir.m_x, dir.m_y };
		bullet.speed = config.bulletSpeed;
		bullet.parent = this;

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