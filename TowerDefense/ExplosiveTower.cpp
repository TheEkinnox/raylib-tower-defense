#include "pch.h"
#include <Vector/Vector2.h>
#include "TowerDefenseGameManager.h"
#include "ExplosiveTower.h"
#include "ConfigTower.h"


namespace TD
{
	ExplosiveTower::ExplosiveTower(Vector2 position) : ITower()
	{
		if (!config.LoadFromFile(BulletType::EXPLOSIVE, level))
			throw;

		Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();
		const Texture* towerTexture = renderer.GetTexture("Assets/textures/PNG/Default size/towerDefense_tile270.png");
		m_sprite = &renderer.CreateSprite(*towerTexture, position, ENTITY_LAYER);

		GameMap& map = TowerDefenseGameManager::GetInstance().Map;
		const float scale = map.GetScale();
		m_sprite->SetScale(scale);
	}
	
	void ExplosiveTower::LevelUp()
	{
		if (level == config.maxLevel)
			return;

		level++; // add payment here.

		if (!config.LoadFromFile(config.bulletType, level))
			throw;
	}

	void ExplosiveTower::ShootAt(const Enemy& enemy)
	{
		if (GetTime() < m_nextShootTime)
			return;

		Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();
		const Texture* bulletTexture = renderer.GetTexture("Assets/textures/PNG/Default size/towerDefense_tile252.png");

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

	void ExplosiveTower::Update()
	{
		if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_E))
			LevelUp();

		Enemy* enemy = CheckRange();

		if (enemy != nullptr)
			ShootAt(*enemy);

		m_bulletPool.Update();
	}
	void ExplosiveTower::OnBulletCollision(Enemy& enemy)
	{
	
		EnemyArmy& enemyArmy = TowerDefenseGameManager::GetInstance().EnemyArmy;
		const GameMap& map = TowerDefenseGameManager::GetInstance().Map;
		const float scale = map.GetScale();

		std::vector<Enemy*>& enemyList = enemyArmy.GetArmy();
		LibMath::Vector2 enemyPos;
		LibMath::Vector2 bulletPos(enemy.Position().x, enemy.Position().y);
		const float squaredRange = TILE_WIDTH * scale * TILE_HEIGHT * scale;

		for (size_t i = 0; i < enemyList.size(); i++)
		{
			enemyPos = { enemyList[i]->Position().x, enemyList[i]->Position().y };

			if (bulletPos.distanceSquaredFrom(enemyPos) <= squaredRange)
				enemyList[i]->Damage(config.damage);
		}
	}
}