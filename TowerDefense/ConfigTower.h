#pragma once
#include <string>
#include <raylib.h> // Color
#include "BulletType.h"

#define MAX_LEVEL 3
#define TOWER_CONFIG_PATH_FORMAT "Assets/towers/tower_%d_%d.cfg"
#define TOWER_CONFIG_DATA_COUNT 9

namespace TD
{
	class ConfigTower
	{
	public:
		unsigned int	maxLevel = 0;
		float			bulletSpeed = 0;
		float			firingRate = 0;
		float			range = 0;
		unsigned int	damage = 0;
		unsigned int	price = 0;
		unsigned int	sellPrice = 0;
		std::string		texturePath;
		std::string		buttonTexturePath;
		std::string		bulletTexturePath;
		BulletType		bulletType;
		Color			rangeCircleColor = SKYBLUE;
		Color			rangeCircleDangerColor = RED;
		
		bool LoadFromFile(TowerType type, std::uint8_t level);
	};
}