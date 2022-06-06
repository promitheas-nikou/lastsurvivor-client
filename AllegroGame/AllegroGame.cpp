
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

#include "Shader.h"

//ALLEGRO_THREAD* 


static const float TPS = 50.f;

static ALLEGRO_MUTEX* worldMutex;
static ALLEGRO_THREAD* worldTickerThread;

void *WorldTickerFunc(ALLEGRO_THREAD* thr, void* _world)
{
	World* world = (World*)_world;
	ALLEGRO_TIMER* timer = al_create_timer(1/TPS);
	ALLEGRO_EVENT evt;
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_start_timer(timer);
	double a, b;
	a = al_get_time();
	while (!al_get_thread_should_stop(thr))
	{
		al_wait_for_event(queue, &evt);
		if (evt.type != ALLEGRO_EVENT_TIMER)
			continue;
		al_lock_mutex(worldMutex);
		world->Tick();
		b = al_get_time();
		printf("\rTICK: %lf",b-a);
		a = b;
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
	printf("\n======= INITIALIZING QUESTS =======\n\n");
	init_quests();
	printf("\n======= INITIALIZING ENTITIES =======\n\n");
	init_entities();
	double LOAD_TIME = al_get_time();
	printf("\n\n===============================\nDONE LOADING IN %.3lf SECONDS!\n===============================\n\n",LOAD_TIME-BEGIN_TIME);

	//ALLEGRO_SAMPLE* s = al_load_sample("sample1.wav");
	//al_play_sample(s, 1., 1., 1., ALLEGRO_PLAYMODE_LOOP, NULL);
	//printf("SAMPLE: %p\nERROR: %d\n", s, al_get_errno());

	char keys_pressed = 0; //NULL,NULL,NULL,NULL,W,A,S,D

	World* world = World::CreateNewWorld("New World");
	world->entities.push_back(new CactusBossEntity(world, 10, 10));
	double tick;
	double worldDraw;
	double playerGUIdraw;
	double drawEnd;
	printf("\n");
	worldMutex = al_create_mutex();
	worldTickerThread = al_create_thread(&WorldTickerFunc, world);
	al_start_thread(worldTickerThread);
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
				world->player->HandleEvent(NEXT_EVENT);
			}
		}
		
		al_clear_to_color(al_map_rgb(0, 0, 0));
		tick = al_get_time();
		worldDraw = al_get_time();
		
		al_lock_mutex(worldMutex);

		loaded_shaders["world"]->Use();
		world->Draw();
		playerGUIdraw = al_get_time();
		loaded_shaders["default"]->Use();
		world->player->DrawGUI();

		al_unlock_mutex(worldMutex);

		drawEnd = al_get_time();
		al_flip_display();
		tick = worldDraw - tick;
		worldDraw = playerGUIdraw - worldDraw;
		playerGUIdraw = drawEnd - playerGUIdraw;
		//printf("\rTICK: %.3lf WORLD: %.3lf GUI: %.3lf", tick, worldDraw, playerGUIdraw);
	}

	delete world;

	free_resources();
	destroy_graphics();
}