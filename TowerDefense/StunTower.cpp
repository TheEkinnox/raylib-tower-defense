#include "pch.h"
#include "StunTower.h"
#include <Vector/Vector2.h>
#include "TowerDefenseGameManager.h"
#include "ConfigTower.h"


namespace TD
{
	StunTower::StunTower(const Vector2 position) :
		ITower(position, TowerType::STUNNING)
	{
	}

	void StunTower::ShootAt(const Enemy& enemy)
	{
		if (GetTime() < m_nextShootTime)
			return;

		Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();
		const Texture* bulletTexture = renderer.GetTexture("Assets/textures/PNG/Default size/towerDefense_tile272.png");
		Bullet& bullet = m_bulletPool.GetObject(renderer.CreateSprite(*bulletTexture, Position(), Layer::BULLET), *this);

		LibMath::Vector2 dir(enemy.Position().x - Position().x, enemy.Position().y - Position().y);
		dir.normalize();

		bullet.dir = Vector2{ dir.m_x, dir.m_y };
		bullet.speed = config.bulletSpeed;

		const float rotation = dir.angleFrom(LibMath::Vector2::right()).degree() + 90;
		m_sprite->SetRotation(rotation);

		m_nextShootTime = GetTime() + static_cast<double>(1 / config.firingRate);
	};

	void StunTower::Update()
	{
		if (IsKeyPressed(KEY_TWO))
			LevelUp();

		ITower::Update();
	}

	void StunTower::OnBulletCollision(Enemy& enemy)
	{
		enemy.Stun(STUN_TIME);
		enemy.Damage(config.damage);
	}
}