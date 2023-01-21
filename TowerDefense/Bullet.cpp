#include "pch.h"
#include "Bullet.h"
#include "TowerDefenseGameManager.h"

namespace TD
{
	Bullet::Bullet(TD::Sprite& sprite) : Sprite(&sprite)
	{
		GameMap& map = TowerDefenseGameManager::GetInstance().Map;
		const float scale = map.GetScale();
		Sprite->SetScale(scale);
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

		TowerDefenseGameManager& gameManager = TowerDefenseGameManager::GetInstance();
		GameMap& map = gameManager.Map;
		Renderer& renderer = gameManager.GetRenderer();

		unsigned int mapWidth = map.GetWidth() * TILE_WIDTH * map.GetScale();
		unsigned int mapHeight = (map.GetHeight()-1) * TILE_HEIGHT * map.GetScale();

		if (Position().x < 0 || Position().x > mapWidth || Position().y < 0 || Position().y > mapHeight)
		{
			renderer.RemoveSprite(*Sprite);
			SetActive(false);
		}

		//if (::Enemy.pos == pos )
	};

}