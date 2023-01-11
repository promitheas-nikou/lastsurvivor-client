#pragma once
#include <string>

enum class SoundType {
	TILE_WALK,
	TILE_BREAK,
	TILE_PLACE,
	ENTITY_IDLE,
	ENTITY_WALK,
	ENTITY_HURT,
	PROJECTILE_LAUNCH,
	PROJECTILE_HIT,
	NONE
};

SoundType GetSoundTypeFromString(std::string str);