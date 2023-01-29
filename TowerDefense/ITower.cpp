#include "pch.h"
#include <raylib.h>
#include <Vector.h>

#include "TowerDefenseGameManager.h"
#include "ITower.h"
#include "ConfigTower.h"

namespace TD
{
	Pool<Bullet>	ITower::m_bulletPool{};
	size_t			ITower::m_towersCount{0};

	ITower::ITower(const Vector2 position, const TowerType type) : level(1), upgradeCost(), config(), m_nextShootTime()
	{
		if (!config.LoadFromFile(type, 1))
			throw;

		Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();
		const Texture* towerTexture = renderer.GetTexture(config.texturePath);
		m_sprite = &renderer.CreateSprite(*towerTexture, position, Layer::ENTITY);

		const GameMap& map = TowerDefenseGameManager::GetInstance().Map;
		const float scale = map.GetScale();
		m_sprite->SetScale(scale);

		m_towersCount++;
	}

	ITower::~ITower()
	{
		m_towersCount--;

		if (m_towersCount == 0)
			m_bulletPool.Clear();
	}

	void ITower::Update()
	{
		const auto& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();
		const Vector2 scale = renderer.GetRenderScale();
		const Vector2 offset = renderer.GetRenderPosition();

		const Vector2 pos
		{
			m_sprite->Position().x * scale.x + offset.x,
			m_sprite->Position().y * scale.y + offset.y
		};

		const Vector2 mousePos = GetMousePosition();
		const float width = static_cast<float>(m_sprite->GetTexture().width) * scale.x;
		const float height = static_cast<float>(m_sprite->GetTexture().height) * scale.y;

		if (mousePos.x >= pos.x - width / 2 && mousePos.x <= pos.x + width / 2 &&
			mousePos.y >= pos.y - height / 2 && mousePos.y <= pos.y + height / 2)
		{
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
				LevelUp();
			}
			else if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))
			{

				auto& gameManager = TowerDefenseGameManager::GetInstance();
				gameManager.Player.AddMoney(config.sellPrice);
				gameManager.Map.RemoveTower(this);
				return;
			}
		}

		const Enemy* enemy = CheckRange();

		if (enemy != nullptr)
			ShootAt(*enemy);

		m_bulletPool.Update();
	}

	void ITower::LevelUp()
	{
		Player& player = TowerDefenseGameManager::GetInstance().Player;
		if (level == config.maxLevel)
			return;
		
		ConfigTower upConfig;

		if (!upConfig.LoadFromFile(config.bulletType, level + 1))
			throw;

		if (player.Money < upConfig.price)
			return;

		level++;

		config = upConfig;

		player.RemoveMoney(config.price);


		Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();
		m_sprite->SetTexture(*renderer.GetTexture(config.texturePath));
	}

	void ITower::ShootAt(const Enemy& enemy)
	{
		if (GetTime() < m_nextShootTime)
			return;

		Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();
		const Texture* bulletTexture = renderer.GetTexture(config.bulletTexturePath);
		Bullet& bullet = m_bulletPool.GetObject(renderer.CreateSprite(*bulletTexture, Position(), Layer::BULLET), *this);

		LibMath::Vector2 dir(enemy.Position().x - Position().x, enemy.Position().y - Position().y);
		dir.normalize();

		bullet.dir = Vector2{ dir.m_x, dir.m_y };
		bullet.speed = config.bulletSpeed;

		const float rotation = dir.angleFrom(LibMath::Vector2::right()).degree() + 90;
		m_sprite->SetRotation(rotation);

		m_nextShootTime = GetTime() + static_cast<double>(1 / config.firingRate);
	}

	Enemy* ITower::CheckRange()
	{
		EnemyArmy& enemyArmy = TowerDefenseGameManager::GetInstance().EnemyArmy;
		const GameMap& map = TowerDefenseGameManager::GetInstance().Map;
		const float scale = map.GetScale();

		const std::vector<Enemy*>& enemyList = enemyArmy.GetArmy();
		const LibMath::Vector2 towerPos(Position().x, Position().y);
		const float squaredRange = config.range * config.range * TILE_WIDTH * scale * TILE_HEIGHT * scale;

		for (size_t i = 0; i < enemyList.size(); i++)
		{
			LibMath::Vector2 enemyPos = {enemyList[i]->Position().x, enemyList[i]->Position().y};

			if (towerPos.distanceSquaredFrom(enemyPos) <= squaredRange)
				return enemyList[i];
		}
		return nullptr;
	}
}