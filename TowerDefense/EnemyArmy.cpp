#include "pch.h"
#include "EnemyArmy.h"
#include "Enemy.h"
#include "HealerEnemy.h"
#include "TowerDefenseGameManager.h"

TD::EnemyArmy::~EnemyArmy()
{
	for (const Enemy* enemy : m_enemies)
		delete enemy;

	m_enemies.clear();
}

void TD::EnemyArmy::RemoveEnemy(const Enemy& enemy)
{
	for (size_t i = 0; i < m_enemies.size(); i++)
	{
		if (&enemy == m_enemies[i])
		{
			delete m_enemies[i];

			for (size_t j = i + 1; j < m_enemies.size(); j++)
				m_enemies[j - 1] = m_enemies[j];

			m_enemies.resize(m_enemies.size() - 1);
			return;
		}
	}
}

void TD::EnemyArmy::ClearEnemies()
{
	for (const Enemy* enemy : m_enemies)
		delete enemy;

	m_enemies.clear();
}

std::vector<TD::Enemy*>& TD::EnemyArmy::GetArmy()
{
	return m_enemies;
}

void TD::EnemyArmy::Update()
{
#ifdef _DEBUG
	if (IsKeyPressed(KEY_W))
	{
		if (IsKeyDown(KEY_LEFT_CONTROL))
		{
			ClearEnemies();
		}
		else
		{
			SpawnEnemy<Enemy>(EnemyType::TANK);
			SpawnEnemy<HealerEnemy>(EnemyType::HEALER);
			SpawnEnemy<Enemy>(EnemyType::SCOUT);
		}
	}
#endif

	for (Enemy* enemy : m_enemies)
		if (enemy != nullptr)
			enemy->Update();
}

Vector2 TD::EnemyArmy::GetSpawnPosition()
{
	const TowerDefenseGameManager& gameManager = TowerDefenseGameManager::GetInstance();

	return gameManager.Map.GetSpawnPosition();
}
