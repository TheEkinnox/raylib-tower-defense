#pragma once
#include <string>

#include "EnemyType.h"

#define ENEMY_CONFIG_PATH_FORMAT "Assets/enemies/enemy_%d.cfg"
#define ENEMY_CONFIG_DATA_COUNT 5

namespace TD
{
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
