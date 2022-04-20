#include "SoundType.h"

SoundType GetSoundTypeFromString(std::string str)
{
	if (str == "tile_walk")
		return SoundType::TILE_WALK;
	if (str == "tile_break")
		return SoundType::TILE_BREAK;
	if (str == "tile_place")
		return SoundType::TILE_PLACE;
	if (str == "entity_hurt")
		return SoundType::ENTITY_HURT;
	if (str == "entity_idle")
		return SoundType::ENTITY_IDLE;
	if (str == "entity_walk")
		return SoundType::ENTITY_WALK;
	if (str == "projectile_hit")
		return SoundType::PROJECTILE_HIT;
	if (str == "projectile_launch")
		return SoundType::PROJECTILE_LAUNCH;
	return SoundType::NONE;
}
