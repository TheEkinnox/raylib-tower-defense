#include "pch.h"
#include "StunTower.h"
#include <Vector/Vector2.h>
#include "TowerDefenseGameManager.h"
#include "ConfigTower.h"


namespace TD
{
	StunTower::StunTower(const Vector2 position) :
		ITower(position, BulletType::STUNNING)
	{
	}

	void StunTower::ShootAt(const Enemy& enemy)
	{
		if (GetTime() < m_nextShootTime)
			return;

		Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();
		const Texture* bulletTexture = renderer.GetTexture("Assets/textures/PNG/Default size/towerDefense_tile272.png");
		Bullet& bullet = m_bulletPool.GetObject(renderer.CreateSprite(*bulletTexture, Position(), ENTITY_LAYER + 1), *this);

		LibMath::Vector2 dir(enemy.Position().x - Position().x, enemy.Position().y - Position().y);
		dir.normalize();

		bullet.dir = Vector2{ dir.m_x, dir.m_y };
		bullet.speed = config.bulletSpeed;

		m_nextShootTime = GetTime() + static_cast<double>(1 / config.firingRate);
	};

	void StunTower::Update()
	{
		if (IsKeyPressed(KEY_TWO))
			LevelUp();

		Enemy* enemy = CheckRange();

		if (enemy != nullptr)
			ShootAt(*enemy);

		m_bulletPool.Update();
	}

	void StunTower::OnBulletCollision(Enemy& enemy)
	{
		enemy.Stun(STUN_TIME);
		enemy.Damage(config.damage);
	}
}