#include "Graphics.h"

void init_graphics()
{
	al_init();
	al_init_font_addon();
	al_init_ttf_addon();

	main_display = al_create_display(1000, 700);
	if (main_display == NULL)
	{
		printf("FAILED TO INITIALIZE DISPLAY...\nABORTING...\n");
		exit(EXIT_FAILURE);
	}
}

void destroy_graphics()
{
	al_destroy_display(main_display);
}
