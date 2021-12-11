#include "Graphics.h"
#include "ResourceLoader.h"
#include <allegro5/allegro_image.h>

ALLEGRO_DISPLAY* main_display;

void init_graphics()
{
	printf("INITIALIZING GRAPHICS COMPONENTS...\n");
	if(!al_init_font_addon())
		exit(EXIT_FAILURE);
	if(!al_init_ttf_addon())
		exit(EXIT_FAILURE);
	if(!al_init_image_addon())
		exit(EXIT_FAILURE);
	printf("ALL GRAPHICS COMPONENTS SUCCESSFULLY INITIALIZED!\n");
}

void init_window()
{
	printf("CREATING DISPLAY...\n");
	al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
	main_display = al_create_display(1000, 700);
	if (main_display == NULL)
	{
		printf("FAILED TO INITIALIZE DISPLAY...\nABORTING...\n");
		exit(EXIT_FAILURE);
	}
	printf("DISPLAY SUCCESSFULLY CREATED!\n");
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
