#include "Graphics.h"
#include "ResourceLoader.h"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "Logging.h"

ALLEGRO_EVENT_QUEUE* event_queue;

ALLEGRO_DISPLAY* main_display;

int SCREEN_WIDTH = 1000;
int SCREEN_HEIGHT = 600;

void init_graphics()
{
	lsg_write_to_session_log(INFO,"INITIALIZING GRAPHICS COMPONENTS...");
	if(!al_init_font_addon())
		exit(EXIT_FAILURE);
	if(!al_init_ttf_addon())
		exit(EXIT_FAILURE);
	if (!al_init_image_addon())
		exit(EXIT_FAILURE);
	lsg_write_to_session_log(INFO, "ALL GRAPHICS COMPONENTS SUCCESSFULLY INITIALIZED!");
}

void init_sound()
{
	lsg_write_to_session_log(INFO, "INITIALIZING AUDIO...");
	if (!al_install_audio())
		lsg_write_to_session_log(ERROR, "FAILED TO INSTALL AUDIO!!! PROCEEDING INITIALIZATION WITH NO AUDIO!!!");
	if(!al_init_acodec_addon())
		lsg_write_to_session_log(ERROR, "FAILED TO INSTALL AUDIO!!!PROCEEDING INITIALIZATION WITH NO AUDIO!!!");
	al_reserve_samples(40);
	lsg_write_to_session_log(INFO, "AUDIO SUCCESSFULLY INITIALIZED!");
}

void init_window()
{
	lsg_write_to_session_log(INFO, "CREATING DISPLAY...");
	al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE | ALLEGRO_FULLSCREEN_WINDOW);
	//al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);
	//al_set_new_display_option(ALLEGRO_SWAP_METHOD, 1, ALLEGRO_REQUIRE);
	main_display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	SCREEN_WIDTH = al_get_display_width(main_display);
	SCREEN_HEIGHT = al_get_display_height(main_display);
	if (main_display == NULL)
	{
		lsg_write_to_session_log(FATAL, "FAILED TO INITIALIZE DISPLAY!!! ABORTING!!!");
		exit(EXIT_FAILURE);
	}
	if (!al_install_keyboard()) {
		lsg_write_to_session_log(FATAL, "FAILED TO INITIALIZE KEYBOARD!!! ABORTING!!!");
		exit(EXIT_FAILURE);
	}
	if (!al_install_mouse()) {
		lsg_write_to_session_log(FATAL, "FAILED TO INITIALIZE MOUSE!!! ABORTING!!!");
		exit(EXIT_FAILURE);
	}
	event_queue = al_create_event_queue();
	lsg_register_textlog_event_listener(event_queue);
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(main_display));
	al_set_separate_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA, ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
	lsg_write_to_session_log(INFO, "DISPLAY SUCCESSFULLY CREATED!");
}

ALLEGRO_EVENT NEXT_EVENT;
bool GetNextEvent()
{
	return al_get_next_event(event_queue, &NEXT_EVENT);
}

void config_window()
{
	lsg_write_to_session_log(INFO, "CONFIGURING DISPLAY...");
	al_set_window_title(main_display, game_name.c_str());
	al_set_display_icon(main_display, window_icon);
	lsg_write_to_session_log(INFO, "DISPLAY SUCCESSFULLY CONFIGURED!");
}

void destroy_graphics()
{
	al_destroy_display(main_display);
}
