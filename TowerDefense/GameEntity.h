#pragma once
#include <raylib.h>

namespace TD
{
	class Sprite;

	class GameEntity
	{
	public:
						GameEntity();
		explicit		GameEntity(Sprite& sprite);
		virtual			~GameEntity();

		const Sprite&	GetSprite() const;
		Vector2			Position() const;
		Vector2&		Position();

	protected:
		Sprite*			m_sprite;
	};
}
