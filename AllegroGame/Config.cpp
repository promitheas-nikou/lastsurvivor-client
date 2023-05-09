#include "Config.h"


ALLEGRO_COLOR gameconfig::SOLID_BACKGROUND_COLOR_0 = al_map_rgba(255, 255, 255, 255);
ALLEGRO_COLOR gameconfig::SOLID_BACKGROUND_COLOR_1 = al_map_rgba(180, 180, 180, 255);
ALLEGRO_COLOR gameconfig::SOLID_BACKGROUND_COLOR_2 = al_map_rgba(130, 130, 130, 255);
ALLEGRO_COLOR gameconfig::SOLID_BACKGROUND_COLOR_3 = al_map_rgba(100, 100, 100, 255);
ALLEGRO_COLOR gameconfig::SOLID_TEXT_COLOR_NORMAL = al_map_rgba(0, 0, 0, 255);
ALLEGRO_COLOR gameconfig::SOLID_TEXT_COLOR_ALT = al_map_rgba(180, 180, 180, 255);
ALLEGRO_COLOR gameconfig::SOLID_TEXT_COLOR_OK = al_map_rgba(0, 255, 0, 255);
ALLEGRO_COLOR gameconfig::SOLID_TEXT_COLOR_WARN = al_map_rgba(255, 255, 0, 255);
ALLEGRO_COLOR gameconfig::SOLID_TEXT_COLOR_ERROR = al_map_rgba(255, 0, 0, 255);
ALLEGRO_COLOR gameconfig::TRANSPARENT_BACKGROUND_COLOR = al_map_rgba(150, 150, 150, 150);
ALLEGRO_COLOR gameconfig::TEXT_COLOR = al_map_rgba(0, 0, 0, 255);
ALLEGRO_COLOR gameconfig::ALT_TEXT_COLOR = al_map_rgba(100,100,100,255);

ALLEGRO_COLOR gameconfig::PLAYER_MENU_SEMI_TRANSPARENT_MENU_COLOR_0 = al_map_rgba(0, 150, 255, 150);
ALLEGRO_COLOR gameconfig::PLAYER_MENU_SEMI_TRANSPARENT_MENU_COLOR_1 = al_map_rgba(150, 255, 0, 150);
ALLEGRO_COLOR gameconfig::PLAYER_MENU_SEMI_TRANSPARENT_MENU_COLOR_2 = al_map_rgba(0, 200, 130, 150);

ALLEGRO_COLOR gameconfig::PLAYER_MENU_PROGBAR_BACK_COLOR_0 = al_map_rgba(150, 0, 0, 150);
ALLEGRO_COLOR gameconfig::PLAYER_MENU_PROGBAR_FILL_COLOR_0 = al_map_rgba(255, 0, 0, 150);
ALLEGRO_COLOR gameconfig::PLAYER_MENU_PROGBAR_BACK_COLOR_1 = al_map_rgba(150, 150, 150, 150);
ALLEGRO_COLOR gameconfig::PLAYER_MENU_PROGBAR_FILL_COLOR_1 = al_map_rgba(150, 150, 150, 150);

ALLEGRO_COLOR gameconfig::PLAYER_MENU_SEMI_TRANSPARENT_TEXT_COLOR_0 = al_map_rgba(255, 0, 0, 150);
ALLEGRO_COLOR gameconfig::PLAYER_MENU_SEMI_TRANSPARENT_TEXT_COLOR_1 = al_map_rgba(255, 255, 255, 150);

ALLEGRO_COLOR gameconfig::PLAYER_MENU_CONSUMABLES_HOTBAR_COLOR = al_map_rgba(255, 0, 0, 255);
ALLEGRO_COLOR gameconfig::PLAYER_MENU_USABLES_HOTBAR_COLOR = al_map_rgba(0, 255, 0, 255);
ALLEGRO_COLOR gameconfig::PLAYER_MENU_PLACEABLES_HOTBAR_COLOR = al_map_rgba(0, 0, 255, 255);
int gameconfig::GUI_DEFAULT_LINE_HEIGHT = 64;
int gameconfig::GUI_DEFAULT_SLOT_SIZE = 128;
int gameconfig::GUI_DEFAULT_TEXT_SIZE = 30;
float gameconfig::GUI_SCALE = 1.0f;

float gameconfig::GetSlotSize()
{
	return GUI_DEFAULT_SLOT_SIZE * GUI_SCALE;
}

int gameconfig::GetTextSize()
{
	return GUI_DEFAULT_TEXT_SIZE * GUI_SCALE;
}

float gameconfig::GetLineHeight()
{
	return GUI_DEFAULT_LINE_HEIGHT*GUI_SCALE;
}

int gameconfig::GetTileSize()
{
	return 128;
}
