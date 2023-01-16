#pragma once
#include <raylib.h>
#include "bullettype.h"

using namespace std;

namespace TD
{
	struct Bullet // public structure
	{
		Vector2 pos;				// position of the bullet
		Vector2 dir;				// direction of the bullet 
		float speed = 2;			// the speed is two pixel per move
		//BulletType ;
		//Sprite : TD::Sprite*

		void Update();
		void spawnBullet();
	};
}