#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <Windows.h>
#include "World.h"
#include <cstdio>
#include "Graphics.h"
#include "ResourceLoader.h"
#include "Reflection.h"

#include "Shader.h"

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
	printf("\n======= LOADING RESOURCES =======\n\n");
	load_resources();
	printf("\n======= PREPARING DISPLAY =======\n\n");
	init_window();
	config_window();
	printf("\n======= LOADING SHADERS =======\n\n");
	load_shaders();
	printf("\n\n===============================\nINITIALIZING GAME\n===============================\n\n");
	printf("\n======= INITIALIZING TILES =======\n\n");
	init_tiles();
	double LOAD_TIME = al_get_time();
	printf("\n\n===============================\nDONE LOADING IN %.3lf SECONDS!\n===============================\n\n",LOAD_TIME-BEGIN_TIME);

	loaded_shaders[1]->Use();

	World world;
	world.GetTile(-17, -5);
	while (true)
	{
		al_clear_to_color(al_map_rgb(0, 0, 0));
		world.Draw();
		al_flip_display();
	}

	free_resources();
	destroy_graphics();
}