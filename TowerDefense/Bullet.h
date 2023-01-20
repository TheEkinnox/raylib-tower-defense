#pragma once
#include <raylib.h>
#include "bullettype.h"
#include "PooledObject.h"
#include "Sprite.h"

namespace TD
{
	class Bullet : public PooledObject
	{
	public:
		Bullet(Sprite& sprite);
		//LibMath::Vector2 dir;		// direction of the bullet
		//BulletType;
		TD::Sprite* Sprite;
		float speed = 20;			// the speed is twenty pixel per sec

		Vector2 Position() const;
		Vector2& Position();

		void Update()override;
	};
}