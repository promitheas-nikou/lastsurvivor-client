#pragma once
#include "SoundType.h"
#include "AudioMultiTrack.h"
#include <map>
#include "json.h"

class AudioMultiTrackCollection
{
private:
	mutable std::map<SoundType, AudioMultiTrack*> multiTracks;
public:


	AudioMultiTrackCollection() = default;
	void Play(SoundType t) const;
	void Link(SoundType t, AudioMultiTrack* m);
	void LoadFromJSON(nlohmann::json data);
};

