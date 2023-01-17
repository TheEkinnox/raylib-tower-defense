#include "pch.h"
#include "Bullet.h"


namespace TD
{

	void Bullet::Update()
	{
		if (IsKeyPressed (KEY_SPACE) ) // temporary set for test 
		{
			spawnBullet ();
			pos.x += speed;
			pos.y += speed;
		}
	};

	void Bullet::spawnBullet ()
	{
		DrawRectangle( pos.x, pos.y, 4, 4, RED);
	}
}