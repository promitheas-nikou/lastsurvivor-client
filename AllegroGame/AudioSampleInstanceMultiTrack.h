#pragma once
#include <vector>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>
#include "AudioMultiTrack.h"

class AudioSampleInstanceMultiTrack:
	public AudioMultiTrack
{
private:
	mutable ALLEGRO_SAMPLE_INSTANCE* lastPlaying;
	std::vector<ALLEGRO_SAMPLE_INSTANCE*> *sampleInstances;
public:

	AudioSampleInstanceMultiTrack(std::vector<ALLEGRO_SAMPLE_INSTANCE*>& si);

	virtual void Play() const final;
};

