#pragma once
#include <vector>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>
#include "AudioMultiTrack.h"

class AudioSampleMultiTrack:
	public AudioMultiTrack
{
private:
	std::vector<ALLEGRO_SAMPLE*> *samples;
public:

	AudioSampleMultiTrack(std::vector<ALLEGRO_SAMPLE*>& si);

	virtual void Play() const final;
};

