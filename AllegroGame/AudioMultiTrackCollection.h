#pragma once
#include "AudioMultiTrack.h"
#include "SoundType.h"
#include <map>
#include "json.h"

class AudioMultiTrackCollection
{
private:
	std::map<SoundType, AudioMultiTrack*> audioTracks;
public:
	void Link(SoundType t, AudioMultiTrack* a);
	void Play(SoundType t);
	void LoadFromJSON(nlohmann::json data);
};

