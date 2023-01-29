#include "pch.h"
#include "Enemy.h"

#include <stdexcept>
#include <Arithmetic.h>
#include <Vector/Vector2.h>

#include "AStar.h"
#include "EnemyArmy.h"
#include "TowerDefenseGameManager.h"

namespace TD
{
	Enemy::Enemy(const EnemyType type, EnemyArmy& army, const Vector2 position) :
		GameEntity(), m_config(type), m_army(&army), m_remainingStunTime(0), m_currentTarget{ -1, -1 }
	{
		if (!m_config.LoadFromFile())
			throw runtime_error("Unable to load the enemy's configuration file.");

		TowerDefenseGameManager& gameManager = TowerDefenseGameManager::GetInstance();
		Renderer& renderer = gameManager.GetRenderer();
		const Texture& texture = *renderer.GetTexture(m_config.TexturePath);
		m_sprite = &renderer.CreateSprite(texture, position, Layer::ENTITY);

		const GameMap& map = gameManager.Map;
		m_sprite->SetScale(map.GetScale());

		ai::Graph mapGraph = map.GetGraph();

		const Vector2 cellPos = map.GetCellPosition(position);
		const Vector2 hqCellPos = map.GetCellPosition(map.GetPlayerHQPosition());
		ai::ManhattanHeuristic heuristic(hqCellPos.x, hqCellPos.y);

		m_pathFinder = new ai::AStarPathFinder(heuristic);

		const uint32_t index = map.PositionToIndex(cellPos);
		const uint32_t hqIndex = map.PositionToIndex(hqCellPos);

		ai::Node* enemyNode = mapGraph.GetNode(index);
		ai::Node* hqNode = mapGraph.GetNode(hqIndex);

		if (enemyNode == nullptr || hqNode == nullptr ||
			!m_pathFinder->PathFind(mapGraph, *enemyNode, *hqNode))
			throw runtime_error("Unable to find a path to the HQ.");
	}

	Enemy::~Enemy()
	{
		TowerDefenseGameManager::GetInstance().GetRenderer().RemoveSprite(*m_sprite);
		delete m_pathFinder;
	}

	void Enemy::Update()
	{
		const GameMap& map = TowerDefenseGameManager::GetInstance().Map;

		Vector2 targetCell = m_currentTarget;
		const Vector2 targetVec = map.GetScreenPosition(targetCell);
		const LibMath::Vector2 targetPos(targetVec.x, targetVec.y);

		if (targetCell.x < 0 || targetCell.y < 0 ||
			targetPos.distanceSquaredFrom({Position().x, Position().y}) < TILE_WIDTH * map.GetScale() * ENEMY_TILE_THRESHOLD)
		{
			const uint32_t index = map.PositionToIndex(map.GetCellPosition(Position()));
			const ai::Edge* targetEdge = m_pathFinder->GetPathEdge(index);

			if (targetEdge == nullptr)
			{
				HitHQ();
				return;
			}

			targetCell = map.IndexToPosition(targetEdge->To->GetIndex());
			m_currentTarget = targetCell;
		}

		MoveTo(targetCell);
	}

	void Enemy::MoveTo(const Vector2 cellPosition)
	{
		if (m_remainingStunTime > 0)
		{
			m_remainingStunTime -= GetFrameTime();
			return;
		}

		const GameMap& map = TowerDefenseGameManager::GetInstance().Map;
		const Vector2 targetVec = map.GetScreenPosition(cellPosition);

		LibMath::Vector2 pos(Position().x, Position().y);
		const LibMath::Vector2 targetPos(targetVec.x, targetVec.y);
		const float deltaSpeed = m_config.Speed * GetFrameTime();

		if (pos.distanceSquaredFrom(targetPos) < deltaSpeed * deltaSpeed)
		{
			Position() = targetVec;
			return;
		}

		LibMath::Vector2 dir = targetPos - pos;
		dir.normalize();

		pos += dir * deltaSpeed;

		Position().x = LibMath::max(pos.m_x, 0);
		Position().y = LibMath::max(pos.m_y, 0);

		const float rotation = acosf(dir.m_x) * RAD2DEG;
		m_sprite->SetRotation(rotation);
	}

	void Enemy::Damage(const unsigned int damage)
	{
		m_config.Life = damage < m_config.Life ? m_config.Life - damage : 0;

		if (m_config.Life == 0)
		{
			auto& gameManager = TowerDefenseGameManager::GetInstance();
			gameManager.Player.AddMoney(m_config.Gold);
			m_army->RemoveEnemy(*this);
		}
	}

	void Enemy::Heal(const unsigned int amount)
	{
		m_config.Life = std::min(m_config.Life + amount, m_config.MaxLife);
	}

	void Enemy::Stun(const float duration)
	{
		m_remainingStunTime = duration;
	}

	void Enemy::HitHQ() const
	{
		TowerDefenseGameManager::GetInstance().Player.Damage(m_config.Damage);
		m_army->RemoveEnemy(*this);
	}
}
