#include "pch.h"
#include "Enemy.h"
#include "EnemyArmy.h"
#include "HealerEnemy.h"
#include "TowerDefenseGameManager.h"

namespace TD
{
	EnemyArmy::EnemyArmy() : m_config()
	{
	}

	EnemyArmy::~EnemyArmy()
	{
		for (const Enemy* enemy : m_enemies)
			delete enemy;

		m_enemies.clear();
	}

	void EnemyArmy::RemoveEnemy(const Enemy& enemy)
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

	void EnemyArmy::ClearEnemies()
	{
		for (const Enemy* enemy : m_enemies)
			delete enemy;

		m_enemies.clear();
	}

	std::vector<Enemy*>& EnemyArmy::GetArmy()
	{
		return m_enemies;
	}

	bool EnemyArmy::Load(const std::string& filePath)
	{
		return m_config.LoadFromFile(filePath);
	}

	void EnemyArmy::Update()
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

		const float frameTime = GetFrameTime();

		if (m_config.Warmup > 0)
		{
			m_config.Warmup -= frameTime;
		}
		else
		{
			for (EnemyWave& wave : m_config.Waves)
				wave.Update(*this);
		}

		for (Enemy* enemy : m_enemies)
			if (enemy != nullptr)
				enemy->Update();
	}

	Vector2 EnemyArmy::GetSpawnPosition()
	{
		const TowerDefenseGameManager& gameManager = TowerDefenseGameManager::GetInstance();

		return gameManager.Map.GetSpawnPosition();
	}
}
