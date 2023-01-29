#include "pch.h"
#include "Enemy.h"
#include "EnemyArmy.h"
#include "HealerEnemy.h"
#include "TowerDefenseGameManager.h"

namespace TD
{
	EnemyArmy::EnemyArmy() : m_timer(0), m_currentWave(1), m_config()
	{
	}

	EnemyArmy::~EnemyArmy()
	{
		ClearEnemies();
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

		m_config.Waves.clear();

		m_enemies.clear();
	}

	std::vector<Enemy*>& EnemyArmy::GetArmy()
	{
		return m_enemies;
	}

	unsigned EnemyArmy::GetCurrentWave() const
	{
		return m_currentWave;
	}

	bool EnemyArmy::Load(const std::string& filePath)
	{
		ClearEnemies();

		m_timer = 0;
		m_currentWave = 1;
		return m_config.LoadFromFile(filePath);
	}

	void EnemyArmy::Update()
	{
		m_timer += GetFrameTime();
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
		bool areAllWavesClear = true;

		if (m_timer > m_config.Warmup)
		{
			for (EnemyWave& wave : m_config.Waves)
			{
				wave.Update(*this);
				areAllWavesClear = areAllWavesClear && wave.EnemiesToSpawn.empty();
			}
		}
		else
		{
			areAllWavesClear = false;
		}

		for (Enemy* enemy : m_enemies)
			if (enemy != nullptr)
				enemy->Update();

		if (areAllWavesClear && m_enemies.empty())
		{
			for (EnemyWave& wave : m_config.Waves)
				wave.Reset();

			m_timer = 0;
			m_currentWave++;
		}
	}

	Vector2 EnemyArmy::GetSpawnPosition()
	{
		const TowerDefenseGameManager& gameManager = TowerDefenseGameManager::GetInstance();

		return gameManager.Map.GetSpawnPosition();
	}
}
