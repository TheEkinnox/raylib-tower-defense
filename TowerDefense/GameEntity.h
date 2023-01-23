#pragma once
#include <raylib.h>

#define ENTITY_LAYER 1

namespace TD
{
	class Sprite;

	class GameEntity
	{
	public:
						GameEntity();
		explicit		GameEntity(Sprite& sprite);
		virtual			~GameEntity() = default;

		const Sprite&	GetSprite() const;
		Vector2			Position() const;
		Vector2&		Position();

	protected:
		Sprite*			m_sprite;
	};
}
