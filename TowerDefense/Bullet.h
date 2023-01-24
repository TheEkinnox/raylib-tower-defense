#pragma once
#include <raylib.h>
#include <functional>

#include "PooledObject.h"
#include "Sprite.h"

namespace TD
{
	class Enemy;
	class ITower;

	class Bullet : public PooledObject
	{
	public:
		Bullet(Sprite& sprite);
		~Bullet();

		Vector2		dir;			// direction of the bullet
		TD::Sprite*	sprite;
		float		speed;			// the speed of the bullets in pixy/sec  
		ITower*		parent;

		Vector2		Position() const;
		Vector2&	Position();

		void		Update() override;
		Enemy*		CheckCollision();
	};
}