#pragma once
#include <raylib.h>

namespace TD
{
	class Sprite;

	class GameEntity
	{
	public:
		explicit		GameEntity(Sprite& sprite);
		virtual			~GameEntity() = default;

		const Sprite&	GetSprite() const;
		Vector2			Position() const;
		Vector2&		Position();

	protected:
		Sprite*			m_sprite;
	};
}
