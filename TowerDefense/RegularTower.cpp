#include "pch.h"
#include "RegularTower.h"

namespace TD
{
	RegularTower::RegularTower(Sprite& sprite) : ITower(sprite)
	{}

	void RegularTower::ShootAt()
	{
		TD::Sprite *bulletSprite = new Sprite(LoadTexture("Assets/textures/PNG/Default size/towerDefense_tile275.png"), Position());

		m_bulletPool.GetObject<Bullet>(*bulletSprite);
	};

	void RegularTower::Update()
	{
		if (IsKeyPressed(KEY_R))
			ShootAt();

		m_bulletPool.Update();

		m_sprite->Draw();
	}
}