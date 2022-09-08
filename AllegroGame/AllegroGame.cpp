#include "AllegroGame.h"

#define _CRT_SECURE_NO_WARNINGS
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <Windows.h>
#include "World.h"
#include <cstdio>
#include "MathUtils.h"
#include "Graphics.h"
#include "ResourceLoader.h"
#include "ZombieEntity.h"
#include "CactusBossEntity.h"
#include "DebugInfo.h"

#include "Shader.h"

//ALLEGRO_THREAD* 

static const float TPS = 50.f;

GUI* currentGUI;
GUI* mainMenuGUI;
GUI* playMenuGUI;
GUI* creditsMenuGUI;
GUI* worldCreationGUI;
World* world;
bool doWorldTick;

ALLEGRO_MUTEX* worldMutex;
ALLEGRO_THREAD* worldTickerThread;

void *WorldTickerFunc(ALLEGRO_THREAD* thr, void* nothing)
{
	ALLEGRO_TIMER* timer = al_create_timer(1/TPS);
	ALLEGRO_EVENT evt;
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_start_timer(timer);
	while (!al_get_thread_should_stop(thr))
	{
		al_wait_for_event(queue, &evt);
		if (evt.type != ALLEGRO_EVENT_TIMER)
			continue;
		if (!doWorldTick)
			continue;
		al_lock_mutex(worldMutex);
		world->Tick();
		al_unlock_mutex(worldMutex);
	}
	return NULL;
}

void EXIT_GAME()
{
	al_set_thread_should_stop(worldTickerThread);
	al_join_thread(worldTickerThread, NULL);
	destroy_graphics();
	exit(EXIT_SUCCESS);
}

#include <allegro5/allegro.h>
#include <allegro5/allegro5.h>
#include <allegro5/alcompat.h>

#include <iostream>

int main()
{
	doWorldTick = false;
	if (!al_init())
	{
		printf("FATAL ALLEGRO LIB LOADING ERROR!!!\n");
		exit(EXIT_FAILURE);
	}
	double BEGIN_TIME = al_get_time();
	printf("LOADING...\n\n\n");
	printf("\n======= GRAPHICS =======\n\n");
	init_graphics();
	printf("\n======= AUDIO =======\n\n");
	init_sound();
	printf("\n======= LOADING RESOURCES =======\n\n");
	load_resources();
	printf("\n======= PREPARING DISPLAY =======\n\n");
	init_window();
	config_window();
	printf("\n======= LOADING SHADERS =======\n\n");
	load_shaders();
	//printf("\n\n======	=========================\nINITIALIZING GAME\n===============================\n\n");
	printf("\n======= INITIALIZING ITEMS =======\n\n");
	init_items();
	printf("\n======= INITIALIZING TILES =======\n\n");
	init_tiles();
	printf("\n======= LOADING RECIPES =======\n\n");
	init_recipes();
	printf("\n======= INITIALIZING ENTITIES =======\n\n");
	init_entities();
	World::Init();
	double LOAD_TIME = al_get_time();
	printf("\n\n===============================\nDONE LOADING IN %.3lf SECONDS!\n===============================\n\n",LOAD_TIME-BEGIN_TIME);

	al_play_sample(loaded_audio_samples["themes.menu"][0], 1., 1., 1., ALLEGRO_PLAYMODE_LOOP, NULL);

	char keys_pressed = 0; //NULL,NULL,NULL,NULL,W,A,S,D

	printf("\n");
	worldMutex = al_create_mutex();
	worldTickerThread = al_create_thread(&WorldTickerFunc, world);
	al_start_thread(worldTickerThread);
	mainMenuGUI = new MainMenuGUI();
	playMenuGUI = new PlayMenuGUI();
	worldCreationGUI = new WorldCreationMenuGUI();
	creditsMenuGUI = new CreditsMenuGUI();
	currentGUI = mainMenuGUI;
	while (true)
	{
		while (GetNextEvent())
		{
			switch (NEXT_EVENT.type)
			{
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				EXIT_GAME();
				break;
			default:
				currentGUI->HandleEvent(NEXT_EVENT);
			}
		}
		
		al_clear_to_color(al_map_rgb(0, 0, 0));

		currentGUI->DrawGUI();
		DebugInfo::framesEnd.push(al_get_time());
		if (DebugInfo::framesEnd.size() > DebugInfo::FRAMES_RECORD_NUM)
			DebugInfo::framesEnd.pop();

		al_flip_display();
	}

	delete world;

	free_resources();
	destroy_graphics();
}