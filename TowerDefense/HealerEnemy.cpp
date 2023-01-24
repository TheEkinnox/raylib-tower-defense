#include "pch.h"
#include <fstream>
#include <vector>
#include <Vector/Vector2.h>

#include "HealerEnemy.h"
#include "EnemyArmy.h"
#include "TowerDefenseGameManager.h"
#include "utility.h"


TD::HealerEnemy::HealerEnemy(const EnemyType type, EnemyArmy& army, const Vector2 position) :
	Enemy(type, army, position), m_healRange(0), m_healAmount(0), m_healCooldown(0),
	m_nextHealTime(0)
{
	char const* configPath = TextFormat(ENEMY_CONFIG_PATH_FORMAT, m_config.Type);

	std::ifstream fileStream(configPath);

	if (!fileStream.is_open())
		throw; // TODO: throw the adequate exception

	std::string	curLine;
	int loadedCount = 0;

	while (std::getline(fileStream, curLine) && loadedCount < ENEMY_CONFIG_DATA_COUNT)
	{
		curLine = Trim(RemoveComments(curLine));

		if (curLine.empty())
			continue;

		std::vector<std::string> tokens = SplitString(curLine, " ", false);

		if (tokens.size() < 2)
			continue;

		if (tokens[0] == "heal_range")
		{
			m_healRange = std::stof(tokens[1]);
			loadedCount++;
		}
		else if (tokens[0] == "heal_cooldown")
		{
			m_healCooldown = std::stof(tokens[1]);
			m_nextHealTime = GetTime() + static_cast<double>(m_healCooldown);
			loadedCount++;
		}
		else if (tokens[0] == "heal_amount")
		{
			m_healAmount = std::stoul(tokens[1]);
			loadedCount++;
		}
	}

	if (loadedCount != HEALER_DATA_COUNT)
		throw; // TODO: throw the adequate exception
}

void TD::HealerEnemy::HealAround()
{
	if (!m_army || GetTime() < m_nextHealTime)
		return;

	const GameMap& map = TowerDefenseGameManager::GetInstance().Map;
	const float scale = map.GetScale();
	const float squaredRange = m_healRange * m_healRange * TILE_WIDTH * scale * TILE_HEIGHT * scale;

	const std::vector<Enemy*>& enemies = m_army->GetArmy();
	const LibMath::Vector2 healerPos(Position().x, Position().y);

	bool healedAllies = false;

	for (Enemy* enemy : enemies)
	{
		if (enemy == this)
			continue;

		LibMath::Vector2 enemyPos = {enemy->Position().x, enemy->Position().y};

		if (healerPos.distanceSquaredFrom(enemyPos) <= squaredRange)
		{
			enemy->Heal(m_healAmount);
			healedAllies = true;
		}
	}

	if (!healedAllies)
		Heal(m_healAmount);

	m_nextHealTime = GetTime() + static_cast<double>(m_healCooldown);
}

void TD::HealerEnemy::Update()
{
	Enemy::Update();

	HealAround();
}
