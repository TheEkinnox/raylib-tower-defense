#pragma once
#include <raylib.h>
#include <vector>
#include "Enemy.h"

namespace TD
{
	enum class EnemyType;
	class Enemy;

	class EnemyArmy
	{
	public:
		EnemyArmy() = default;
		~EnemyArmy();

		template<typename T>
		T*						SpawnEnemy(EnemyType type);
		void					RemoveEnemy(const Enemy& enemy);
		void					ClearEnemies();
		std::vector<Enemy*>&	GetArmy();
		void					Update();

	private:
		std::vector<Enemy*>		m_enemies;

		static Vector2			GetSpawnPosition();
	};

	template <typename T>
	T* EnemyArmy::SpawnEnemy(const EnemyType type)
	{
		if (!std::is_base_of_v<Enemy, T>)
			throw; // TODO: throw the adequate exception

		T* enemy = new T(type, *this, GetSpawnPosition());

		m_enemies.push_back(enemy);
		return enemy;
	}
}
