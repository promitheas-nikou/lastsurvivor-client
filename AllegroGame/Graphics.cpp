#include "Graphics.h"
#include "ResourceLoader.h"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>

ALLEGRO_EVENT_QUEUE* event_queue;

ALLEGRO_DISPLAY* main_display;

int SCREEN_WIDTH = 1000;
int SCREEN_HEIGHT = 600;

void init_graphics()
{
	printf("INITIALIZING GRAPHICS COMPONENTS...\n");
	if(!al_init_font_addon())
		exit(EXIT_FAILURE);
	if(!al_init_ttf_addon())
		exit(EXIT_FAILURE);
	if (!al_init_image_addon())
		exit(EXIT_FAILURE);
	printf("ALL GRAPHICS COMPONENTS SUCCESSFULLY INITIALIZED!\n");
}

void init_sound()
{
	if (!al_install_audio())
		printf("FAILED TO INSTALL AUDIO!!!\nWILL PROCEED INITIALIZATION WITH NO AUDIO\n");
}

void init_window()
{
	printf("CREATING DISPLAY...\n");
	al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE | ALLEGRO_FULLSCREEN_WINDOW);
	//al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);
	//al_set_new_display_option(ALLEGRO_SWAP_METHOD, 1, ALLEGRO_REQUIRE);
	main_display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	SCREEN_WIDTH = al_get_display_width(main_display);
	SCREEN_HEIGHT = al_get_display_height(main_display);
	if (main_display == NULL)
	{
		printf("FAILED TO INITIALIZE DISPLAY...\nABORTING...\n");
		exit(EXIT_FAILURE);
	}
	if (!al_install_keyboard()) {
		printf("FAILED TO INITIALIZE KEYBOARD...\nABORTING...\n");
		exit(EXIT_FAILURE);
	}
	if (!al_install_mouse()) {
		printf("FAILED TO INITIALIZE MOUSE...\nABORTING...\n");
		exit(EXIT_FAILURE);
	}
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(main_display));
	printf("DISPLAY SUCCESSFULLY CREATED!\n");
}

ALLEGRO_EVENT NEXT_EVENT;
bool GetNextEvent()
{
	return al_get_next_event(event_queue, &NEXT_EVENT);
}

void config_window()
{
	printf("CONFIGURING DISPLAY...\n");
	al_set_window_title(main_display, game_name.c_str());
	al_set_display_icon(main_display, window_icon);
	printf("DISPLAY SUCCESSFULLY CONFIGURED!\n");
}

void destroy_graphics()
{
	al_destroy_display(main_display);
}
