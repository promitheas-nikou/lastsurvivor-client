#include "AudioSampleMultiTrack.h"

AudioSampleMultiTrack::AudioSampleMultiTrack(std::vector<ALLEGRO_SAMPLE*>& si) : samples{ &si }
{}


void AudioSampleMultiTrack::Play() const
{
	ALLEGRO_SAMPLE* s = (*samples)[rand() % samples->size()];
	al_play_sample(s, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);	
}
