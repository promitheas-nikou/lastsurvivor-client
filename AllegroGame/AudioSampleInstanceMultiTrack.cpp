#include "AudioSampleInstanceMultiTrack.h"

AudioSampleInstanceMultiTrack::AudioSampleInstanceMultiTrack(std::vector<ALLEGRO_SAMPLE_INSTANCE*>& si) : sampleInstances{ &si }, lastPlaying{ nullptr }
{}


void AudioSampleInstanceMultiTrack::Play() const
{
	if (lastPlaying != nullptr)
		if (al_get_sample_instance_playing(lastPlaying))
			return;
	ALLEGRO_SAMPLE_INSTANCE* s = (*sampleInstances)[rand() % sampleInstances->size()];
	lastPlaying = s;
	al_play_sample_instance(s);	
}

void AudioSampleInstanceMultiTrack::Stop() const
{
	al_stop_sample_instance(lastPlaying);
}
