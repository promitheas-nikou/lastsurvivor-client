#include "AudioMultiTrack.h"

AudioMultiTrack::AudioMultiTrack(std::vector<ALLEGRO_SAMPLE_INSTANCE*>& si) : sampleInstances{ &si }
{}


void AudioMultiTrack::Play() const
{
	//al_play_sample_instance((*sampleInstances)[rand() % sampleInstances->size()]);
}
