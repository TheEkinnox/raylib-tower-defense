#include "pch.h"
#include "Enemy.h"

#include <Arithmetic.h>
#include <Vector/Vector2.h>

#include "EnemyArmy.h"
#include "TowerDefenseGameManager.h"

namespace TD
{
	Enemy::Enemy(const EnemyType type, EnemyArmy& army, const Vector2 position) :
		GameEntity(), m_config(type), m_army(&army), m_nextHitTime(0)
	{
		if (!m_config.LoadFromFile())
			throw;

		if (m_config.AttackRate > 0.f)
			m_nextHitTime = GetTime() + static_cast<double>(1.f / m_config.AttackRate);

		TowerDefenseGameManager& gameManager = TowerDefenseGameManager::GetInstance();
		Renderer& renderer = gameManager.GetRenderer();
		const Texture& texture = *renderer.GetTexture(m_config.TexturePath);
		m_sprite = &renderer.CreateSprite(texture, position, ENTITY_LAYER);
		m_sprite->SetScale(gameManager.Map.GetScale());
	}

	Enemy::~Enemy()
	{
		TowerDefenseGameManager::GetInstance().GetRenderer().RemoveSprite(*m_sprite);
	}

	void Enemy::Update()
	{
		if (stunTime > 0)
		{
			stunTime -= GetFrameTime();
			return;
		}

		LibMath::Vector2 pos(Position().x, Position().y);

		const GameMap& map = TowerDefenseGameManager::GetInstance().Map;
		const Vector2 hqPos = map.GetPlayerHQPosition();

		// TODO: Use path-finding to get the target pos
		const float scaledWidth = static_cast<float>(m_sprite->GetTexture().width) * map.GetScale();
		const LibMath::Vector2 target(hqPos.x - scaledWidth, hqPos.y);

		LibMath::Vector2 dir = target - pos;
		dir.normalize();

		pos += dir * m_config.Speed * GetFrameTime();

		if (LibMath::abs(target.m_x - pos.m_x) > .5f)
			Position().x = LibMath::max(pos.m_x, 0);
		else
			Position().x = target.m_x;

		if (LibMath::abs(target.m_y - pos.m_y) > .5f)
			Position().y = LibMath::max(pos.m_y, 0);
		else
			Position().y = target.m_y;
	}
	

	void Enemy::Damage(const unsigned int damage)
	{
		m_config.Life = damage < m_config.Life ? m_config.Life - damage : 0;

		if (m_config.Life == 0)
			m_army->RemoveEnemy(*this);
	}

	void Enemy::Heal(const unsigned int amount)
	{
		m_config.Life = std::min(m_config.Life + amount, m_config.MaxLife);
	}

	void Enemy::Stun(float duration)
	{
		stunTime = duration;
	}
}
