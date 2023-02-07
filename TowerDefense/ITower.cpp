#include "pch.h"
#include <raylib.h>
#include <Vector.h>

#include "TowerDefenseGameManager.h"
#include "ITower.h"

#include "App.h"
#include "ConfigTower.h"

namespace TD
{
	Pool<Bullet>	ITower::m_bulletPool{ BULLET_POOL_START_SIZE };
	size_t			ITower::m_towersCount{ 0 };

	ITower::ITower(const Vector2 position, const TowerType type) :
		level(1), upgradeCost(), config(), m_shootTimer(), m_rangeTexture{}
	{
		if (!config.LoadFromFile(type, 1))
			throw;

		const GameMap& map = TowerDefenseGameManager::GetInstance().Map;
		const float scale = map.GetScale();

		Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();
		const Texture* towerTexture = renderer.GetTexture(config.texturePath);

		GenerateRangeTexture();
		m_sprite = &renderer.CreateSprite(*towerTexture, position, Layer::TOWER);
		m_rangeSprite = &renderer.CreateSprite(m_rangeTexture.texture, position, Layer::DECALS);

		m_sprite->SetScale(scale);
		m_rangeSprite->SetScale(scale, -scale);
		m_rangeSprite->SetTint(config.rangeCircleColor);

		m_towersCount++;
	}

	ITower::~ITower()
	{
		m_towersCount--;

		if (m_towersCount == 0)
			m_bulletPool.Clear();

		if (m_rangeSprite != nullptr)
		{
			Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();
			renderer.RemoveSprite(*m_rangeSprite);

			UnloadRenderTexture(m_rangeTexture);
		}
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
			m_rangeSprite->Show();

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
		else
		{
			m_rangeSprite->Hide();
		}

		const Enemy* enemy = CheckRange();

		if (enemy != nullptr)
		{
			ShootAt(*enemy);
			m_rangeSprite->SetTint(config.rangeCircleDangerColor);
		}
		else
		{
			m_rangeSprite->SetTint(config.rangeCircleColor);
		}
	}

	void ITower::UpdateBullets()
	{
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

		GenerateRangeTexture();

		Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();
		m_sprite->SetTexture(*renderer.GetTexture(config.texturePath));
		m_rangeSprite->SetTint(config.rangeCircleColor);
	}

	void ITower::ShootAt(const Enemy& enemy)
	{
		m_shootTimer -= App::GetScaledFrameTime();

		if (m_shootTimer > 0)
			return;

		Renderer& renderer = TowerDefenseGameManager::GetInstance().GetRenderer();
		const Texture* bulletTexture = renderer.GetTexture(config.bulletTexturePath);
		Sprite& bulletSprite = renderer.CreateSprite(*bulletTexture, Position(), Layer::BULLET);
		Bullet& bullet = m_bulletPool.GetObject(bulletSprite, *this);

		LibMath::Vector2 dir(enemy.Position().x - Position().x, enemy.Position().y - Position().y);
		dir.normalize();

		bullet.dir = Vector2{ dir.m_x, dir.m_y };
		bullet.speed = config.bulletSpeed;

		const float rotation = dir.signedAngleFrom(LibMath::Vector2::down()).degree();
		m_sprite->SetRotation(rotation);
		bullet.sprite->SetRotation(rotation);

		m_shootTimer = 1 / config.firingRate;
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

	void ITower::GenerateRangeTexture()
	{
		const GameMap& map = TowerDefenseGameManager::GetInstance().Map;
		const float scale = map.GetScale();

		const float scaledRange = config.range * TILE_WIDTH * scale;
		const float rangeDiameter = scaledRange * 2;
		const int intRangeDiameter = static_cast<int>(rangeDiameter);
		const Vector2 rangeCenter
		{
			rangeDiameter / 2,
			rangeDiameter / 2
		};

		UnloadRenderTexture(m_rangeTexture);
		m_rangeTexture.id = 0;

		m_rangeTexture = LoadRenderTexture(intRangeDiameter,
			intRangeDiameter);

		BeginTextureMode(m_rangeTexture);
		ClearBackground(BLANK);

		DrawCircleV(rangeCenter, scaledRange, ColorAlpha(WHITE, .6f));

		DrawRing(rangeCenter, scaledRange - RANGE_CIRCLE_THICKNESS * scale,
			rangeDiameter / 2, 0, 360, 36, WHITE);

		EndTextureMode();

		if (m_rangeSprite != nullptr)
			m_rangeSprite->SetTexture(m_rangeTexture.texture);
	}
}
