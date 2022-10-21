#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include "ItemBundle.h"
#include "QuestCollection.h"
#include <unordered_map>
#include "AudioMultiTrack.h"
#include "Tile.h"
#include "GroundTile.h"
#include "Item.h"
#include "Entity.h"
#include <string>
#include "LootBundle.h"

#include "json.h"
#include "Shader.h"

const extern std::string DATA_JSON_TEXTURE_KEY;
const extern std::string DATA_JSON_TEXTURE0_KEY;
const extern std::string DATA_JSON_TEXTURE1_KEY;
const extern std::string DATA_JSON_TEXTURE2_KEY;
const extern std::string DATA_JSON_TEXTURE3_KEY;
const extern std::string DATA_JSON_TEXTURE_LIST_KEY;
const extern std::string DATA_JSON_MINING_RESISTANCE_KEY;
const extern std::string DATA_JSON_TOOL_TYPE_KEY;
const extern std::string DATA_JSON_NAME_KEY;
const extern std::string DATA_JSON_DESCRIPTION_KEY;
const extern std::string DATA_JSON_DROP_KEY;
const extern std::string DATA_JSON_COLLECT_KEY;
const extern std::string DATA_JSON_ID_KEY;
const extern std::string DATA_JSON_SPEED_KEY;
const extern std::string DATA_JSON_AUDIO_COLLECTION_KEY;
const extern std::string DATA_JSON_SOUND_TYPE_KEY;
const extern std::string DATA_JSON_RANGESQ_KEY;
const extern std::string DATA_JSON_DAMAGE_KEY;
const extern std::string DATA_JSON_FIRE_SPEED_KEY;
const extern std::string DATA_JSON_HEALTH_KEY;
const extern std::string DATA_JSON_MAX_HEALTH_KEY;
const extern std::string DATA_JSON_HUNGER_KEY;
const extern std::string DATA_JSON_MASS_KEY;
const extern std::string DATA_JSON_WATER_KEY;
const extern std::string DATA_JSON_BURN_TIME_KEY;
const extern std::string DATA_JSON_BURN_HEAT_KEY;
const extern std::string DATA_JSON_BRIGHTNESS_KEY;
const extern std::string DATA_JSON_DURABILITY_KEY;

extern nlohmann::json json_data;

extern std::string game_name;
extern std::string game_version_name;
extern int game_version_major;
extern int game_version_minor;

extern ALLEGRO_BITMAP* window_icon;

extern std::unordered_map<std::string, std::map<int, ALLEGRO_FONT*>> loaded_fonts;
extern std::unordered_map<std::string, ALLEGRO_BITMAP*> loaded_bitmaps;
extern std::unordered_map<std::string, LootBundle*> loaded_loot_bundles;
extern std::unordered_map<std::string, AudioMultiTrack*> loaded_audio_multi_tracks;
extern std::unordered_map<std::string, std::vector<ALLEGRO_SAMPLE*>> loaded_audio_samples;
extern std::unordered_map<std::string, std::vector<ALLEGRO_SAMPLE_INSTANCE*>> loaded_audio_sample_instances;
extern std::unordered_map<std::string, ALLEGRO_MOUSE_CURSOR*> loaded_cursors;
extern std::unordered_map<std::string, Shader*> loaded_shaders;

extern std::map<uint32_t, std::string> tile_ids_to_keys;
extern std::map<uint32_t, std::string> gtile_ids_to_keys;
extern std::map<uint32_t, std::string> item_ids_to_keys;
extern std::map<uint32_t, std::string> entity_ids_to_keys;
extern std::unordered_map<std::string, uint32_t> tile_keys_to_ids;
extern std::unordered_map<std::string, uint32_t> gtile_keys_to_ids;
extern std::unordered_map<std::string, uint32_t> item_keys_to_ids;
extern std::unordered_map<std::string, uint32_t> entity_keys_to_ids;

void load_resources();

void init_tiles();
void init_items();
void init_entities();
void init_recipes();

void load_shaders();

void free_resources();
