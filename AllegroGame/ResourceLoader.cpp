#include "ResourceLoader.h"
#include "Logging.h"
#include <allegro5/error.h>
#include <allegro5/allegro_acodec.h>
#include <fstream>
#include <iostream>
#include <Windows.h>
#include "ItemBundle.h"
#include "GrassGroundTile.h"
#include "DirtGroundTile.h"
#include "StoneGroundTile.h"
#include "SandGroundTile.h"
#include "WaterGroundTile.h"
#include "ListAllTiles.h"
#include "ListAllItems.h"
#include "SimpleItemBundle.h"
#include "CactusBossEntity.h"
#include "ZombieEntity.h"
#include "PlayerEntity.h"
#include "CowPassiveEntity.h"
#include "SheepPassiveEntity.h"
#include "PigPassiveEntity.h"
#include "AudioMultiTrackCollection.h"
#include "AudioSampleInstanceMultiTrack.h"
#include "AudioSampleMultiTrack.h"
#include "LootBundle.h"
#include "MalachiteOreGroundTile.h"
#include "AzuriteOreGroundTile.h"
#include "HematiteOreGroundTile.h"
#include "MagnetiteOreGroundTile.h"
#include "TorchTile.h"
#include "BurnerFurnaceMk1Tile.h"
#define _INIT_TILE(classname){classname::Init(tile_data[classname::ID]);prototype_tiles[classname::ID] = new classname(nullptr, 0, 0);}
#define _INIT_GTILE(classname){classname::Init(ground_tile_data[classname::ID]);prototype_gtiles[classname::ID] = new classname(nullptr, 0, 0);}
#define _INIT_ITEM(classname){classname::Init(item_data[classname::ID]);prototype_items[classname::ID] = new classname();}

#include "Recipe.h"

#define DEBUG

#include <iostream>

const std::string DATA_JSON_TEXTURE_KEY = "texture";
const std::string DATA_JSON_TEXTURE0_KEY = "texture0";
const std::string DATA_JSON_TEXTURE1_KEY = "texture1";
const std::string DATA_JSON_TEXTURE2_KEY = "texture2";
const std::string DATA_JSON_TEXTURE3_KEY = "texture3";
const std::string DATA_JSON_TEXTURE_LIST_KEY = "textures";
const std::string DATA_JSON_MINING_RESISTANCE_KEY = "mining_resistance";
const std::string DATA_JSON_TOOL_TYPE_KEY = "tool";
const std::string DATA_JSON_NAME_KEY = "name";
const std::string DATA_JSON_DESCRIPTION_KEY = "description";
const std::string DATA_JSON_DROP_KEY = "drops";
const std::string DATA_JSON_COLLECT_KEY = "collection_drops";
const std::string DATA_JSON_ID_KEY = "id"; 
const std::string DATA_JSON_DAMAGE_KEY = "damage";
const std::string DATA_JSON_SOUND_TYPE_KEY = "type";
const std::string DATA_JSON_SPEED_KEY = "speed";
const std::string DATA_JSON_AUDIO_COLLECTION_KEY = "audio";
const std::string DATA_JSON_RANGESQ_KEY = "rangesq";
const std::string DATA_JSON_FIRE_SPEED_KEY = "projectile_speed";
const std::string DATA_JSON_HEALTH_KEY = "health";
const std::string DATA_JSON_MAX_HEALTH_KEY = "max_health";
const std::string DATA_JSON_HUNGER_KEY = "hunger";
const std::string DATA_JSON_MASS_KEY = "mass";
const std::string DATA_JSON_WATER_KEY = "water";
const std::string DATA_JSON_BURN_TIME_KEY = "burn_time";
const std::string DATA_JSON_BURN_HEAT_KEY = "burn_heat";
const std::string DATA_JSON_BRIGHTNESS_KEY = "brightness";
const std::string DATA_JSON_DURABILITY_KEY = "durability";
const std::string DATA_JSON_CONVEYOR_MAX_ITEMS_KEY = "conveyor_max_items";
const std::string DATA_JSON_CONVEYOR_SPEED_KEY = "conveyor_speed";
const std::string DATA_JSON_CONVEYOR_ITEM_DISTANCE_KEY = "conveyor_item_dist";
const std::string DATA_JSON_TILE_ID_KEY = "tile";

nlohmann::json json_data;

std::unordered_map<std::string, ALLEGRO_MOUSE_CURSOR*> loaded_cursors;
std::unordered_map<std::string, ALLEGRO_BITMAP*> loaded_bitmaps;	
std::unordered_map<std::string, std::vector<ALLEGRO_SAMPLE*>> loaded_audio_samples;
std::unordered_map<std::string, std::vector<ALLEGRO_SAMPLE_INSTANCE*>> loaded_audio_sample_instances;
std::unordered_map<std::string, AudioMultiTrack*> loaded_audio_multi_tracks;
std::unordered_map<std::string, Shader*> loaded_shaders;
std::unordered_map<std::string, LootBundle*> loaded_loot_bundles;
std::unordered_map<std::string, std::map<int, ALLEGRO_FONT*>> loaded_fonts;

using json = nlohmann::json;

std::unordered_map<std::string, json> ground_tile_data;
std::unordered_map<std::string, json> tile_data;
std::unordered_map<std::string, json> item_data;
std::unordered_map<std::string, json> entity_data;

std::map<uint32_t, std::string> tile_ids_to_keys;
std::map<uint32_t, std::string> gtile_ids_to_keys;
std::map<uint32_t, std::string> item_ids_to_keys;
std::map<uint32_t, std::string> entity_ids_to_keys;
std::unordered_map<std::string, uint32_t> tile_keys_to_ids;
std::unordered_map<std::string, uint32_t> gtile_keys_to_ids;
std::unordered_map<std::string, uint32_t> item_keys_to_ids;
std::unordered_map<std::string, uint32_t> entity_keys_to_ids;

std::string game_name;
std::string game_version_name;
int game_version_major;
int game_version_minor;

ALLEGRO_BITMAP* window_icon;

void load_resources()
{
	try
	{
		json_data = json::parse(std::ifstream("data.json"));

		game_name = json_data["NAME"];
		game_version_name = json_data["VERSION"];

		json textures = json_data["textures"];

		lsg_write_to_session_log(INFO, "CURRENT DIRECTORY: \"%s\"", al_get_current_directory());

		lsg_write_to_session_log(INFO, "LOADING %d TEXTURE(S):", textures.size());

		for (json texture_data : textures)
		{
			std::string id = texture_data["id"];
			std::string filename = texture_data["filename"];
			al_set_new_bitmap_flags(ALLEGRO_CONVERT_BITMAP | ALLEGRO_MIPMAP | ALLEGRO_MIN_LINEAR);
			if ((loaded_bitmaps[id] = al_load_bitmap(("textures/"+filename).c_str())) == NULL)
				lsg_write_to_session_log(WARNING, "\tFAILED TO LOAD TEXTURE 's'(\"%s\")...", id.c_str(), filename.c_str());
			else
				lsg_write_to_session_log(VERBOSE, "\tSUCCESSFULLY LOADED TEXTURE '%s'(\"%s\")...", id.c_str(), filename.c_str());
		}
		window_icon = loaded_bitmaps[(std::string)json_data["WINDOW_ICON"]];
		lsg_write_to_session_log(INFO, "WINDOW ICON IS TEXTURE #%s", ((std::string)json_data["WINDOW_ICON"]).c_str());

		nlohmann::json audios_data = json_data["audio"];
		lsg_write_to_session_log(INFO, "LOADING %d AUDIO SAMPLES...", audios_data.size());
		for (nlohmann::json audio : audios_data)
		{
			std::string id = audio["id"];
			nlohmann::json files = audio["filenames"];
			lsg_write_to_session_log(INFO, "\tLOADING AUDIO MULTITRACK '%s':", id.c_str());
			for (std::string fn : files)
			{
				ALLEGRO_SAMPLE* s;
				//fn = "audio/" + fn;
				if ((s = al_load_sample(("audio/"+fn).c_str())) == NULL)
					lsg_write_to_session_log(WARNING, "\t\tFAILED TO LOAD AUDIO SAMPLE \"%s\"...", fn.c_str());
				else
				{
					lsg_write_to_session_log(VERBOSE, "\t\tSUCCESSFULLY LOADED AUDIO SAMPLE \"%s\"...", fn.c_str());
					ALLEGRO_SAMPLE_INSTANCE* i = al_create_sample_instance(s);
					al_set_sample_instance_playmode(i, ALLEGRO_PLAYMODE_ONCE);
					al_set_sample_instance_speed(i, 1.0f);
					al_attach_sample_instance_to_mixer(i, al_get_default_mixer());
					loaded_audio_samples[id].push_back(s);
					loaded_audio_sample_instances[id].push_back(i);
				}
			}
			bool wait = audio["wait"];
			AudioMultiTrack *a = wait?((AudioMultiTrack*)new AudioSampleInstanceMultiTrack(loaded_audio_sample_instances[id])) : ((AudioMultiTrack*)new AudioSampleMultiTrack(loaded_audio_samples[id]));
			loaded_audio_multi_tracks[id] = a;
		}

		nlohmann::json fonts_data = json_data["fonts"];
		lsg_write_to_session_log(INFO, "LOADING %d FONT(S)...", fonts_data.size());
		

		for (nlohmann::json font : fonts_data)
		{
			std::string id = font["id"];
			std::string fn = font["font"];
			for (int i = 1; i <= 50; i++)
				loaded_fonts[id][i] = al_load_font(fn.c_str(), i, 0);
			for(int i=55;i<=200;i+=5)
				loaded_fonts[id][i] = al_load_font(fn.c_str(), i, 0);
			lsg_write_to_session_log(VERBOSE, "SUCCESSFULLY LOADED FONT '%s'(\"%s\")...", id.c_str(), fn.c_str());
		}

		nlohmann::json cursor_data = json_data["cursors"];
		for (nlohmann::json cd : cursor_data)
		{
			std::string id = cd["id"];
			std::string t = cd["texture"];
			ALLEGRO_BITMAP* b = loaded_bitmaps[t];
			int hotx = cd["hotx"];
			int hoty = cd["hoty"];
			loaded_cursors[id] = al_create_mouse_cursor(b, hotx, hoty);
		}
		InventoryGUI::Init();
	}
	catch (const nlohmann::detail::parse_error& err)
	{
#undef ERROR
		lsg_write_to_session_log(ERROR,"ERROR PARSING \'data.json\'!!! DETAILS:\n%s",err.what());
		exit(EXIT_FAILURE);
	}
}

void load_shaders()
{
	json shaders = json_data["shaders"];

	loaded_shaders["default"] = new Shader("default");

	for (json texture_data : shaders)
	{
		std::string id = texture_data["id"];
		std::string vertex = texture_data["vertex"];
		std::string fragment = texture_data["fragment"];
		loaded_shaders[id] = new Shader(id, vertex.c_str(), fragment.c_str());
	}

}

void init_tiles()
{
	//try {
	lsg_write_to_session_log(INFO, "PARSING TILE DATA... ");
		json __ground_tiles = json_data["ground_tiles"];
		json __tiles = json_data["tiles"];
		for (json td : __ground_tiles)
			ground_tile_data[td[DATA_JSON_ID_KEY]] = td;
		for (json td : __tiles)
			tile_data[td["id"]] = td;
		lsg_write_to_session_log(INFO, "FOUND DATA FOR %d GROUND TILES... ", ground_tile_data.size());
		int counter = 0;
		for (std::pair<std::string, json> pair : ground_tile_data)
		{
			lsg_write_to_session_log(VERBOSE, "FOUND DATA FOR GROUND TILE \"%s\" (\"%s\") ", ((std::string)pair.second[DATA_JSON_ID_KEY]).c_str(), ((std::string)pair.second[DATA_JSON_NAME_KEY]).c_str());
			gtile_ids_to_keys[counter] = pair.first;
			gtile_keys_to_ids[pair.first] = counter++;
		}
		counter = 0;
		lsg_write_to_session_log(INFO, "FOUND DATA FOR %d TILES... ", tile_data.size());
		for (std::pair<std::string, json> pair : tile_data)
		{
			lsg_write_to_session_log(VERBOSE, "FOUND DATA FOR TILE \"%s\" (\"%s\") ", ((std::string)pair.second[DATA_JSON_ID_KEY]).c_str(), ((std::string)pair.second[DATA_JSON_NAME_KEY]).c_str());
			tile_ids_to_keys[counter] = pair.first;
			tile_keys_to_ids[pair.first] = counter++;
		}
		_INIT_GTILE(GrassGroundTile)
		_INIT_GTILE(DirtGroundTile)
		_INIT_GTILE(StoneGroundTile)
		_INIT_GTILE(SandGroundTile)
		_INIT_GTILE(WaterGroundTile)
		_INIT_GTILE(AzuriteOreGroundTile)
		_INIT_GTILE(MalachiteOreGroundTile)
		_INIT_GTILE(HematiteOreGroundTile)
		_INIT_GTILE(MagnetiteOreGroundTile)

		_INIT_TILE(TreeTile)
		_INIT_TILE(BerryBushTile)
		_INIT_TILE(FenceTile)
		_INIT_TILE(TorchTile)
		_INIT_TILE(BurnerFurnaceMk1Tile)
		_INIT_TILE(BrickWallTile)
		_INIT_TILE(StoneBrickWallTile)
		_INIT_TILE(BasicConveyorTile)
		_INIT_TILE(BasicBinTile)

		prototype_tiles[AirTile::ID] = new AirTile(nullptr, 0, 0);
	/* }
	catch (const nlohmann::json::type_error& err)
	{
		fprintf(stderr,"ERROR LOADING TILES!!!\nDETAILS:\n");
		fputs(err.what(), stderr);
		fprintf(stderr, "\n\nEXITING!!!\n");
		exit(EXIT_FAILURE);
	}*/
}

void init_items()
{
#ifndef DEBUG
	try {
#endif //DEBUG
		lsg_write_to_session_log(INFO, "PARSING ITEM DATA... ");
		json __items = json_data["items"];
		json __loot_bundles = json_data["loot_bundles"];
		int counter = 0;
		for (json i : __items)
			item_data[i["id"]] = i;
		lsg_write_to_session_log(INFO, "LOADING %d ITEMS... ", item_data.size());
		for (std::pair<std::string, json> pair : item_data)
		{
			lsg_write_to_session_log(VERBOSE, "FOUND DATA FOR ITEM \"%s\" (\"%s\") ", ((std::string)pair.second[DATA_JSON_ID_KEY]).c_str(), ((std::string)pair.second[DATA_JSON_NAME_KEY]).c_str());
			item_ids_to_keys[counter] = pair.first;
			item_keys_to_ids[pair.first] = counter++;
		}
		_INIT_ITEM(StoneItem)
		_INIT_ITEM(DirtItem)
		_INIT_ITEM(StickItem)
		_INIT_ITEM(SandItem)
		_INIT_ITEM(SimpleSword)
		_INIT_ITEM(GunItem)
		_INIT_ITEM(BerryItem)
		_INIT_ITEM(AnthraciteCoalChunkItem)
		_INIT_ITEM(MalachiteChunkItem)
		_INIT_ITEM(HematiteChunkItem)
		_INIT_ITEM(MagnetiteChunkItem)
		_INIT_ITEM(AzuriteChunkItem)
		_INIT_ITEM(BerryItem)
		_INIT_ITEM(LodestoneItem)
		_INIT_ITEM(SaplingItem)
		_INIT_ITEM(FenceItem)
		_INIT_ITEM(TorchItem)
		_INIT_ITEM(LogItem)
		_INIT_ITEM(CopperIngotItem)
		_INIT_ITEM(IronIngotItem)
		_INIT_ITEM(BurnerFurnaceMk1Item)
		_INIT_ITEM(FlaskItem)
		_INIT_ITEM(CharcoalItem)
		_INIT_ITEM(BrickWallItem)
		_INIT_ITEM(StoneBrickWallItem)
		_INIT_ITEM(RawCowMeatItem)
		_INIT_ITEM(RawPigMeatItem)
		_INIT_ITEM(RawSheepMeatItem)
		_INIT_ITEM(CookedCowMeatItem)
		_INIT_ITEM(CookedPigMeatItem)
		_INIT_ITEM(CookedSheepMeatItem)
		_INIT_ITEM(BoneItem)
		_INIT_ITEM(BasicConveyorItem)
		_INIT_ITEM(SteelIngotItem)
		_INIT_ITEM(CastIronIngotItem)
		_INIT_ITEM(BasicBinItem)
		lsg_write_to_session_log(INFO, "LOADING %d LOOT BUNDLES... ", __loot_bundles.size());
		for (nlohmann::json data : __loot_bundles)
		{
			loaded_loot_bundles[data["id"]] = LootBundle::CreateFromJSON(data);
			lsg_write_to_session_log(VERBOSE, "FOUND DATA FOR LOOT BUNDLE \"%s\" ", ((std::string)data["id"]).c_str());
		}
#ifndef DEBUG
	}
	catch (const nlohmann::json::type_error& err)
	{
		fprintf(stderr, "ERROR LOADING ITEMS!!!\nDETAILS:\n");
		fputs(err.what(), stderr);
		fprintf(stderr, "\n\nEXITING!!!\n");
		exit(EXIT_FAILURE);
	}
#endif //DEBUG
}

void init_entities()
{
	for (nlohmann::json j : json_data["entities"])
		entity_data[j["id"]] = j;
	int counter = 0;
	for (std::pair<std::string, json> pair : entity_data)
	{
		lsg_write_to_session_log(VERBOSE, "FOUND DATA FOR ENTITY \"%s\" (\"%s\")", ((std::string)pair.second[DATA_JSON_ID_KEY]).c_str(), ((std::string)pair.second[DATA_JSON_NAME_KEY]).c_str());
		entity_ids_to_keys[counter] = pair.first;
		entity_keys_to_ids[pair.first] = counter++;
	}
	CactusBossEntity::Init(entity_data[CactusBossEntity::ID]);
	CactusBossEntity::RattleProjectile::Init(entity_data[CactusBossEntity::RattleProjectile::ID]);
	ZombieEntity::Init(entity_data[ZombieEntity::ID]);
	PlayerEntity::Init(entity_data[PlayerEntity::ID]);
	CowPassiveEntity::Init(entity_data[CowPassiveEntity::ID]);
	SheepPassiveEntity::Init(entity_data[SheepPassiveEntity::ID]);
	PigPassiveEntity::Init(entity_data[PigPassiveEntity::ID]);
	prototype_entities[CactusBossEntity::ID] = new CactusBossEntity(nullptr, 0.f, 0.f);
	prototype_entities[CactusBossEntity::RattleProjectile::ID] = new CactusBossEntity::RattleProjectile(nullptr, 0.f, 0.f);
	prototype_entities[ZombieEntity::ID] = new ZombieEntity(nullptr, 0.f, 0.f);
	prototype_entities[PlayerEntity::ID] = new PlayerEntity(nullptr, 0.f, 0.f);
	prototype_entities[CowPassiveEntity::ID] = new CowPassiveEntity(nullptr, 0.f, 0.f);
	prototype_entities[SheepPassiveEntity::ID] = new SheepPassiveEntity(nullptr, 0.f, 0.f);
	prototype_entities[PigPassiveEntity::ID] = new PigPassiveEntity(nullptr, 0.f, 0.f);
	lsg_write_to_session_log(INFO, "SUCCESSFULLY INITIALIZED ENTITIES!");
}

void init_recipes()
{
	CraftingRecipe::LoadRecipes(json_data["recipes"]["crafting"]);
	SmeltingRecipe::LoadRecipes(json_data["recipes"]["smelting"]);
}

void free_resources()
{
	for (std::pair<std::string, ALLEGRO_BITMAP*> p : loaded_bitmaps)
		al_destroy_bitmap(p.second);
	loaded_bitmaps.clear();
	window_icon = NULL;
	for (std::pair<std::string, ALLEGRO_MOUSE_CURSOR*> p : loaded_cursors)
		al_destroy_mouse_cursor(p.second);
	loaded_cursors.clear();
	for(auto m: loaded_fonts)
		for(auto f: m.second)
			al_destroy_font(f.second);
	loaded_fonts.clear();
	for (std::pair<std::string, Shader*> p : loaded_shaders)
	{
		p.second->Delete();
		delete p.second;
	}
}
