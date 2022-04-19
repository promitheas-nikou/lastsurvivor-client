#pragma once
#include <vector>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>

class AudioMultiTrack
{
private:
	mutable ALLEGRO_SAMPLE_INSTANCE* lastPlaying;
	std::vector<ALLEGRO_SAMPLE_INSTANCE*> *sampleInstances;
public:

	AudioMultiTrack(std::vector<ALLEGRO_SAMPLE_INSTANCE*>& si);

	void Play() const;
};

