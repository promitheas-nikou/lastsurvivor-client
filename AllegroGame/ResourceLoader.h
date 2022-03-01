#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "ItemBundle.h"
#include <unordered_map>
#include <string>

#include "json.h"
#include "Shader.h"

const extern std::string DATA_JSON_TEXTURE_KEY;
const extern std::string DATA_JSON_TEXTURE_LIST_KEY;
const extern std::string DATA_JSON_MINING_RESISTANCE_KEY;
const extern std::string DATA_JSON_TOOL_TYPE_KEY;
const extern std::string DATA_JSON_NAME_KEY;
const extern std::string DATA_JSON_DESCRIPTION_KEY;
const extern std::string DATA_JSON_DROP_KEY;
const extern std::string DATA_JSON_ID_KEY;

extern nlohmann::json json_data;

extern std::string game_name;
extern std::string game_version_name;
extern int game_version_major;
extern int game_version_minor;

extern ALLEGRO_BITMAP* window_icon;

extern std::unordered_map<std::string, std::map<int, ALLEGRO_FONT*>> loaded_fonts;
extern std::unordered_map<std::string, ALLEGRO_BITMAP*> loaded_bitmaps;
extern std::unordered_map<std::string, ItemBundle*> loaded_loot_bundles;
extern std::unordered_map<std::string, ALLEGRO_MOUSE_CURSOR*> loaded_cursors;
extern std::unordered_map<std::string, Shader*> loaded_shaders;

void load_resources();

void init_tiles();
void init_items();

void load_shaders();

void free_resources();
