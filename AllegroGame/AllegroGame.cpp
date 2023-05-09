
#define _CRT_SECURE_NO_WARNINGS
#include "AllegroGame.h"
#include "Logging.h"

#include "MainGUIs.h"
#include <Windows.h>
#include "World.h"
#include <cstdio>
#include "MathUtils.h"
#include "Graphics.h"
#include "ResourceLoader.h"
#include "ZombieEntity.h"
#include "CactusBossEntity.h"
#include "DebugInfo.h"
#include <allegro5/allegro_native_dialog.h>

#include "Shader.h"

#define MIN_FPS 20

//ALLEGRO_THREAD* 

const float TPS = 50.f;

GUI* currentGUI;
GUI* mainMenuGUI;
GUI* playMenuGUI;
GUI* creditsMenuGUI;
GUI* worldCreationGUI;
GUI* settingsMenuGUI;
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
	lsg_close_session_logs();
	destroy_graphics();
	exit(EXIT_SUCCESS);
}

#include <iostream>
#include "FixedQueue.h"

extern int mousex;
extern int mousey;

int main()
{
	lsg_open_session_logfile();
	doWorldTick = false;
	if (!al_init())
	{
		lsg_write_to_session_log(FATAL, "FATAL ALLEGRO LIB LOADING ERROR!!!\n%x: %s\n", al_get_errno(), strerror(al_get_errno()));
		exit(EXIT_FAILURE);
	}
	lsg_open_session_textlog();
	double BEGIN_TIME = al_get_time();
	lsg_write_to_session_log(INFO, "STARTING UP...");
	lsg_write_to_session_log(INFO, "===== PREPARING GRAPHICS =====");
	init_graphics();
	lsg_write_to_session_log(INFO, "===== PREPARING AUDIO =====");
	init_sound();
	lsg_write_to_session_log(INFO, "===== LOADING RESOURCES =====");
	load_resources();
	lsg_write_to_session_log(INFO, "===== PREPARING DISPLAY =====");
	init_window();
	config_window();
	lsg_write_to_session_log(INFO, "===== LOADING SHADERS =====");
	load_shaders();
	//printf("\n\n======	=========================\nINITIALIZING GAME\n===============================\n\n");
	lsg_write_to_session_log(INFO, "===== INITIALIZING ITEMS =====");
	init_items();
	lsg_write_to_session_log(INFO, "===== INITIALIZING TILES =====");
	init_tiles();
	lsg_write_to_session_log(INFO, "===== LOADING RECIPES =====");
	init_recipes();
	lsg_write_to_session_log(INFO, "===== INITIALIZING ENTITIES =====");
	init_entities();
	World::Init();
	double LOAD_TIME = al_get_time();
	lsg_write_to_session_log(INFO, "DONE LOADING IN %.3lf SECONDS!",LOAD_TIME-BEGIN_TIME);

	al_set_sample_instance_playmode(loaded_audio_sample_instances["themes.menu"][0], ALLEGRO_PLAYMODE_LOOP);
	al_play_sample_instance(loaded_audio_sample_instances["themes.menu"][0]);

	char keys_pressed = 0; //NULL,NULL,NULL,NULL,W,A,S,D
	printf("\n");
	worldMutex = al_create_mutex();
	worldTickerThread = al_create_thread(&WorldTickerFunc, world);
	al_start_thread(worldTickerThread);
	mainMenuGUI = new MainMenuGUI();
	playMenuGUI = new PlayMenuGUI();
	worldCreationGUI = new WorldCreationMenuGUI();
	creditsMenuGUI = new CreditsMenuGUI();
	settingsMenuGUI = new SettingsMenuGUI();
	currentGUI = mainMenuGUI;
	ALLEGRO_BITMAP* sb = al_create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
	while (true)
	{
		while (GetNextEvent())
		{
			switch (NEXT_EVENT.type)
			{
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				EXIT_GAME();
				break;
			case ALLEGRO_EVENT_DISPLAY_SWITCH_OUT:
				al_clear_keyboard_state(main_display);
				break;
			case ALLEGRO_EVENT_NATIVE_DIALOG_CLOSE:
				lsg_close_session_textlog();
				break;
			default:
				switch (NEXT_EVENT.type) {
				case ALLEGRO_EVENT_MOUSE_AXES:
				case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
				case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY:
				case ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY:
				case ALLEGRO_EVENT_MOUSE_WARPED:
					NEXT_EVENT.mouse.x /= SCREEN_X_SCALE;
					NEXT_EVENT.mouse.dx /= SCREEN_X_SCALE;
					NEXT_EVENT.mouse.y /= SCREEN_Y_SCALE;
					NEXT_EVENT.mouse.dy /= SCREEN_Y_SCALE;
					mousex = NEXT_EVENT.mouse.x;
					mousey = NEXT_EVENT.mouse.y;
				}
				if (NEXT_EVENT.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
					printf("%d:%d\n", NEXT_EVENT.mouse.x, NEXT_EVENT.mouse.y);
				currentGUI->HandleEvent(NEXT_EVENT);
			}
		}
		al_set_target_bitmap(sb);
		al_clear_to_color(al_map_rgb(0, 0, 0));
		currentGUI->DrawGUI();
		DebugInfo::framesEnd.push(al_get_time());
		if (DebugInfo::framesEnd.size() > DebugInfo::FRAMES_RECORD_NUM)
			DebugInfo::framesEnd.pop();

		//al_draw_filled_rectangle(mousex - 5, mousey - 5, mousex + 5, mousey + 5, al_map_rgba(255, 0, 0, 255));
		
		al_set_target_backbuffer(al_get_current_display());
		al_draw_scaled_bitmap(sb, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, PHYSICAL_SCREEN_WIDTH, PHYSICAL_SCREEN_HEIGHT, 0);

		al_flip_display();
	}

	delete world;

	free_resources();
	destroy_graphics();
}