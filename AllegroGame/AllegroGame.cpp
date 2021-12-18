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

static const float DIAG_MOD = 1.4142135623730950488016887242097 / 2;
static const float PLAYER_SPEED = .5f;

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
	while (true)
	{
		while (GetNextEvent())
		{
			switch (NEXT_EVENT.type)
			{
			case ALLEGRO_EVENT_DISPLAY_CLOSE: //WINDOW CLOSED
				EXIT_GAME();
				break;
			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
				break;
			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				break;
			case ALLEGRO_EVENT_MOUSE_AXES: //MOUSE MOVED
				break;
			case ALLEGRO_EVENT_KEY_CHAR:
				break;
			case ALLEGRO_EVENT_KEY_DOWN:
			{
				switch (NEXT_EVENT.keyboard.keycode)
				{
				case ALLEGRO_KEY_W:
					keys_pressed |= 0b00001000;
					break;
				case ALLEGRO_KEY_A:
					keys_pressed |= 0b00000100;
					break;
				case ALLEGRO_KEY_S:
					keys_pressed |= 0b00000010;
					break;
				case ALLEGRO_KEY_D:
					keys_pressed |= 0b00000001;
					break;
				}
			}
				break;
			case ALLEGRO_EVENT_KEY_UP:
			{
				switch (NEXT_EVENT.keyboard.keycode)
				{
				case ALLEGRO_KEY_W:
					keys_pressed &= 0b11110111;
					break;
				case ALLEGRO_KEY_A:
					keys_pressed &= 0b11111011;
					break;
				case ALLEGRO_KEY_S:
					keys_pressed &= 0b11111101;
					break;
				case ALLEGRO_KEY_D:
					keys_pressed &= 0b11111110;
					break;
				}
			}
			break;
				break;
			}
		}
		
		al_clear_to_color(al_map_rgb(0, 0, 0));
		switch (keys_pressed & 0b00001111)
		{
		case 0b0001:
			world.player->warpRelative(PLAYER_SPEED, 0);
			break;
		case 0b0010:
			world.player->warpRelative(0, PLAYER_SPEED);
			break;
		case 0b0011:
			world.player->warpRelative(PLAYER_SPEED * DIAG_MOD, PLAYER_SPEED*DIAG_MOD);
			break;
		case 0b0100:
			world.player->warpRelative(-PLAYER_SPEED, 0);
			break;
		case 0b0110:
			world.player->warpRelative(-PLAYER_SPEED * DIAG_MOD, PLAYER_SPEED * DIAG_MOD);
			break;
		case 0b1000:
			world.player->warpRelative(0, -PLAYER_SPEED);
			break;
		case 0b1001:
			world.player->warpRelative(PLAYER_SPEED * DIAG_MOD, -PLAYER_SPEED * DIAG_MOD);
			break;
		case 0b1100:
			world.player->warpRelative(-PLAYER_SPEED * DIAG_MOD, -PLAYER_SPEED * DIAG_MOD);
			break;
		}
		world.Tick();
		world.Draw();
		loaded_shaders[0]->Use();
		world.player->DrawGUI();
		al_flip_display();
	}

	free_resources();
	destroy_graphics();
}