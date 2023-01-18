#pragma once
#include <raylib.h>

namespace TD
{
	class Sprite;

	class GameEntity
	{
	public:
		explicit		GameEntity(Sprite& sprite);

		const Sprite&	GetSprite() const;
		Vector2			GetPosition() const;
		void			SetPosition(Vector2 position);

	protected:
		Sprite*			sprite;
	};
}
