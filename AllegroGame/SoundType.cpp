#include "SoundType.h"

SoundType GetSoundTypeFromString(std::string str)
{
	if (str == "walk")
		return SoundType::WALK;
	if (str == "run")
		return SoundType::RUN;
	if (str == "break")
		return SoundType::BREAK;
	if (str == "place")
		return SoundType::PLACE;
	return SoundType::NONE;
}
