#pragma once
#include <raylib.h>
#include <string>
#include <vector>
#include "bulletType.h"

#define MAX_LEVEL 3
#define TOWER_CONIFG_PATH_FORMAT "Assets/towers/tower_%d_%d.cfg"
#define TOWER_CONFIG_DATA_COUNT 7

namespace TD
{
	class ConfigTower
	{
	public:
		unsigned int	maxLevel;
		float			bulletSpeed;
		float			firingRate;
		float			range;
		unsigned int	damage;
		unsigned int	price;
		std::string		texturePath;
		TD::BulletType	bulletType;
		
		bool LoadFromFile(BulletType type, std::uint8_t level);
	};
}