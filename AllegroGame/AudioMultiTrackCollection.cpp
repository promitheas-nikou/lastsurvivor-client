#include "AudioMultiTrackCollection.h"
#include "ResourceLoader.h"

void AudioMultiTrackCollection::Link(SoundType t, AudioMultiTrack* a)
{
	audioTracks[t] = a;
}

void AudioMultiTrackCollection::Play(SoundType t)
{
	AudioMultiTrack* a = audioTracks[t];
	if(a!=nullptr)
		a->Play();
}

void AudioMultiTrackCollection::LoadFromJSON(nlohmann::json data)
{
	for (nlohmann::json l : data)
	{
		Link(GetSoundTypeFromString(l[DATA_JSON_SOUND_TYPE_KEY]), loaded_audio_multi_tracks[l[DATA_JSON_ID_KEY]]);
	}
}
