#pragma once
#include <string>
#include "BulletType.h"

#define MAX_LEVEL 3
#define TOWER_CONIFG_PATH_FORMAT "Assets/towers/tower_%d_%d.cfg"
#define TOWER_CONFIG_DATA_COUNT 9

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
		unsigned int	sellPrice;
		std::string		texturePath;
		std::string		buttonTexturePath;
		TD::BulletType	bulletType;
		
		bool LoadFromFile(TowerType type, std::uint8_t level);
	};
}