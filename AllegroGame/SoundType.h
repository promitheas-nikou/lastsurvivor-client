#pragma once
#include <string>

enum class SoundType {
	WALK,
	RUN,
	BREAK,
	PLACE,
	NONE
};

SoundType GetSoundTypeFromString(std::string str);