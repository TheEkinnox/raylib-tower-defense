#pragma once
#include <raylib.h>

#include "PooledObject.h"
#include "Sprite.h"

namespace TD
{
	class Enemy;
	class ITower;

	class Bullet : public PooledObject
	{
	public:
		Bullet();
		Bullet(Sprite& sprite, ITower& parent);
		~Bullet() override;

		Vector2		dir;			// direction of the bullet
		Sprite*		sprite;
		float		speed;			// the speed of the bullets in pixy/sec  
		ITower*		parent;

		Vector2		Position() const;
		Vector2&	Position();

		void		Update() override;
		Enemy*		CheckCollision();
		void		SetActive(bool active) override;
	};
}