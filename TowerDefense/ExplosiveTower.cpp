#include "pch.h"
#include "ExplosiveTower.h"

namespace TD
{
	ExplosiveTower::ExplosiveTower(Sprite& sprite) : ITower(sprite)
	{}

	void ExplosiveTower::ShootAt()
	{
		TD::Sprite *bulletSprite = new Sprite(LoadTexture("Assets/textures/PNG/Default size/towerDefense_tile252.png"), Position());

		m_bulletPool.GetObject<Bullet>(*bulletSprite);
	};

	void ExplosiveTower::Update()
	{
		if (IsKeyPressed(KEY_SPACE))
			ShootAt();

		m_bulletPool.Update();

		m_sprite->Draw();
	}
}