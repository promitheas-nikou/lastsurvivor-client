#include "AudioMultiTrackCollection.h"
#include "ResourceLoader.h"

void AudioMultiTrackCollection::Play(SoundType t) const
{
	AudioMultiTrack* m = multiTracks[t];
	if (m != nullptr)
		m->Play();
}

void AudioMultiTrackCollection::Link(SoundType t, AudioMultiTrack* m)
{
	multiTracks[t] = m;
}

void AudioMultiTrackCollection::LoadFromJSON(nlohmann::json data)
{
	for (nlohmann::json audio : data)
	{
		Link(GetSoundTypeFromString(audio[DATA_JSON_SOUND_TYPE_KEY]), loaded_audio_multi_tracks[audio[DATA_JSON_ID_KEY]]);
	}
}
