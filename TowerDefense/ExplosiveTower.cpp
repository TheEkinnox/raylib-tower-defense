#include "pch.h"
#include <Vector/Vector2.h>
#include "TowerDefenseGameManager.h"
#include "ExplosiveTower.h"
#include "ConfigTower.h"


namespace TD
{
	ExplosiveTower::ExplosiveTower(Vector2 position) :
		ITower(position, TowerType::EXPLOSIVE)
	{
	}

	void ExplosiveTower::ShootAt(const Enemy& enemy)
	{
		if (GetTime() < m_nextShootTime)
			return;

		Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();
		const Texture* bulletTexture = renderer.GetTexture("Assets/textures/PNG/Default size/towerDefense_tile252.png");
		Bullet& bullet = m_bulletPool.GetObject(renderer.CreateSprite(*bulletTexture, Position(), Layer::BULLET), *this);

		LibMath::Vector2 dir(enemy.Position().x - Position().x, enemy.Position().y - Position().y);
		dir.normalize();

		bullet.dir = Vector2{ dir.m_x, dir.m_y };
		bullet.speed = config.bulletSpeed;

		const float rotation = dir.angleFrom(LibMath::Vector2::right()).degree() + 90;
		m_sprite->SetRotation(rotation);
		bullet.sprite->SetRotation(rotation);

		m_nextShootTime = GetTime() + static_cast<double>(1 / config.firingRate);
	};

	void ExplosiveTower::Update()
	{
		if (IsKeyPressed(KEY_THREE))
			LevelUp();

		ITower::Update();
	}

	void ExplosiveTower::OnBulletCollision(Enemy& enemy)
	{
		EnemyArmy& enemyArmy = TowerDefenseGameManager::GetInstance().EnemyArmy;
		const GameMap& map = TowerDefenseGameManager::GetInstance().Map;

		const std::vector<Enemy*>& enemyList = enemyArmy.GetArmy();
		const Vector2 cellPosition = map.GetCellPosition(enemy.Position());

		for (size_t i = 0; i < enemyList.size(); i++)
		{
			const Vector2 enemyCell = map.GetCellPosition(enemyList[i]->Position());

			if (enemyCell.x == cellPosition.x && enemyCell.y == cellPosition.y)
				enemyList[i]->Damage(config.damage);
		}
	}
}