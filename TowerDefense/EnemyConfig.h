#pragma once
#include <string>

#define ENEMY_CONFIG_PATH_FORMAT "Assets/enemies/enemy_%d.cfg"
#define ENEMY_CONFIG_DATA_COUNT 5

namespace TD
{
	enum class EnemyType
	{
		SCOUT,
		TANK,
		HEALER
	};

	struct EnemyConfig
	{
		EnemyType		Type;
		std::string		TexturePath;
		float			Speed;
		unsigned int	Damage;
		unsigned int	Gold;
		unsigned int	Life;
		unsigned int	MaxLife;

		explicit		EnemyConfig(EnemyType type);
		bool			LoadFromFile();
		bool			TryLoadMember(const std::string& line);
	};
}
