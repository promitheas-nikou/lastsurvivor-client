#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <Windows.h>
#include "World.h"
#include <cstdio>
#include "MathUtils.h"
#include "Graphics.h"
#include "ResourceLoader.h"
#include "Reflection.h"

#include "Shader.h"

//ALLEGRO_THREAD* 

void EXIT_GAME()
{
	destroy_graphics();
	exit(EXIT_SUCCESS);
}

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
	//printf("\n\n======	=========================\nINITIALIZING GAME\n===============================\n\n");
	printf("\n======= INITIALIZING TILES =======\n\n");
	init_tiles();
	double LOAD_TIME = al_get_time();
	printf("\n\n===============================\nDONE LOADING IN %.3lf SECONDS!\n===============================\n\n",LOAD_TIME-BEGIN_TIME);

	char keys_pressed = 0; //NULL,NULL,NULL,NULL,W,A,S,D

	World world;
	double tick;
	double worldDraw;
	double playerGUIdraw;
	double drawEnd;
	printf("\n");
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
				world.player->HandleEvent(NEXT_EVENT);
			}
		}
		
		al_clear_to_color(al_map_rgb(0, 0, 0));
		tick = al_get_time();
		world.Tick();
		worldDraw = al_get_time();
		world.Draw();
		playerGUIdraw = al_get_time();
		loaded_shaders[0]->Use();
		world.player->DrawGUI();
		drawEnd = al_get_time();
		al_flip_display();
		tick = worldDraw - tick;
		worldDraw = playerGUIdraw - worldDraw;
		playerGUIdraw = drawEnd - playerGUIdraw;
		printf("\rTICK: %.3lf WORLD: %.3lf GUI: %.3lf", tick, worldDraw, playerGUIdraw);
	}

	free_resources();
	destroy_graphics();
}