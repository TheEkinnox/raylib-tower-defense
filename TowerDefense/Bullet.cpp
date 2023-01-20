#include "pch.h"
#include "Bullet.h"
//#include "TowerDefenseGameManager.h"

namespace TD
{
	Bullet::Bullet(TD::Sprite& sprite) : Sprite(&sprite)
	{
	}

	Vector2 Bullet::Position() const
	{
		return Sprite->Position();
	}

	Vector2& Bullet::Position()
	{
		return Sprite->Position();
	}

	void Bullet::Update()
	{
		Position().x += speed * GetFrameTime() /*dir*/;
		Position().y += speed * GetFrameTime() /*dir*/;

		Sprite->Draw();
		//if (::Enemy.pos == pos )
	};

}