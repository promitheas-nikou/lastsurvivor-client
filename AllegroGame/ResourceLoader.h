#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <map>

#include "json.h"
#include "Shader.h"

extern nlohmann::json json_data;

extern std::string game_name;
extern std::string game_version_name;
extern int game_version_major;
extern int game_version_minor;

extern ALLEGRO_BITMAP* window_icon;

extern std::map<int, std::map<int, ALLEGRO_FONT*>> loaded_fonts;
extern std::map<int, ALLEGRO_BITMAP*> loaded_bitmaps;
extern std::map<int, ALLEGRO_MOUSE_CURSOR*> loaded_cursors;
extern std::map<int, Shader*> loaded_shaders;

void load_resources();

void init_tiles();

void load_shaders();

void free_resources();
