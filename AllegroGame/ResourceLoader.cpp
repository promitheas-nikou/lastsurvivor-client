#include "ResourceLoader.h"
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
#include "AirTile.h"
#include "TreeTile.h"
#include "FenceTile.h"
#include "BerryBushTile.h"
#include "StoneItem.h"
#include "DirtItem.h"
#include "StickItem.h"
#include "SandItem.h"
#include "SimpleSword.h"
#include "GunItem.h"
#include "BerryItem.h"
#include "AnthraciteCoalChunkItem.h"
#include "SimpleItemBundle.h"
#include "CactusBossEntity.h"
#include "ZombieEntity.h"
#include "PlayerEntity.h"
#include "AudioMultiTrackCollection.h"
#include "AudioSampleInstanceMultiTrack.h"
#include "AudioSampleMultiTrack.h"
#include "LootBundle.h"
#include "MalachiteOreGroundTile.h"
#include "AzuriteOreGroundTile.h"
#include "HematiteOreGroundTile.h"
#include "MagnetiteOreGroundTile.h"
#include "HematiteChunkItem.h"
#include "MagnetiteChunkItem.h"
#include "MalachiteChunkItem.h"
#include "AzuriteChunkItem.h"
#include "LodestoneItem.h"
#include "SaplingItem.h"
#include "FenceItem.h"
#include "TorchTile.h"
#include "TorchItem.h"
#include "BurnerFurnaceMk1Tile.h"
#include "BurnerFurnaceMk1Item.h"

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
const std::string DATA_JSON_WATER_KEY = "water";
const std::string DATA_JSON_BURN_TIME_KEY = "burn_time";
const std::string DATA_JSON_BURN_HEAT_KEY = "burn_heat";
const std::string DATA_JSON_BRIGHTNESS_KEY = "brightness";

nlohmann::json json_data;

std::unordered_map<std::string, ALLEGRO_MOUSE_CURSOR*> loaded_cursors;
std::unordered_map<std::string, ALLEGRO_BITMAP*> loaded_bitmaps;	
std::unordered_map<std::string, std::vector<ALLEGRO_SAMPLE*>> loaded_audio_samples;
std::unordered_map<std::string, std::vector<ALLEGRO_SAMPLE_INSTANCE*>> loaded_audio_sample_instances;
std::unordered_map<std::string, AudioMultiTrack*> loaded_audio_multi_tracks;
std::unordered_map<std::string, Shader*> loaded_shaders;
std::unordered_map<std::string, LootBundle*> loaded_loot_bundles;
std::unordered_map<std::string, std::map<int, ALLEGRO_FONT*>> loaded_fonts;

QuestCollection* quest_collection;

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

		printf("CURRENT DIRECTORY: \"%s\"\n\n", al_get_current_directory());

		printf("LOADING %d TEXTURE(S):\n", textures.size());

		for (json texture_data : textures)
		{
			std::string id = texture_data["id"];
			std::string filename = texture_data["filename"];
			al_set_new_bitmap_flags(ALLEGRO_CONVERT_BITMAP | ALLEGRO_MIPMAP | ALLEGRO_MIN_LINEAR);
			if ((loaded_bitmaps[id] = al_load_bitmap(("textures/"+filename).c_str())) == NULL)
				printf("\tFAILED TO LOAD TEXTURE 's'(\"%s\")...\n", id.c_str(), filename.c_str());
			else
				printf("\tSUCCESSFULLY LOADED TEXTURE '%s'(\"%s\")...\n", id.c_str(), filename.c_str());
		}
		window_icon = loaded_bitmaps[(std::string)json_data["WINDOW_ICON"]];
		printf("WINDOW ICON IS TEXTURE #%s\n", ((std::string)json_data["WINDOW_ICON"]).c_str());

		nlohmann::json audios_data = json_data["audio"];
		printf("LOADING %d AUDIO SAMPLES...\n", audios_data.size());
		for (nlohmann::json audio : audios_data)
		{
			std::string id = audio["id"];
			nlohmann::json files = audio["filenames"];
			printf("\tLOADING AUDIO MULTITRACK '%s':\n", id.c_str());
			for (std::string fn : files)
			{
				ALLEGRO_SAMPLE* s;
				//fn = "audio/" + fn;
				if ((s = al_load_sample(("audio/"+fn).c_str())) == NULL)
					printf("\t\tFAILED TO LOAD AUDIO SAMPLE \"%s\"...\n", fn.c_str());
				else
				{
					printf("\t\tSUCCESSFULLY LOADED AUDIO SAMPLE \"%s\"...\n", fn.c_str());
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
		printf("\nLOADING %d FONT(S)...\n", fonts_data.size());	
		

		for (nlohmann::json font : fonts_data)
		{
			std::string id = font["id"];
			std::string fn = font["font"];
			for (int i = 1; i <= 50; i++)
				loaded_fonts[id][i] = al_load_font(fn.c_str(), i, 0);
			for(int i=55;i<=200;i+=5)
				loaded_fonts[id][i] = al_load_font(fn.c_str(), i, 0);
			printf("SUCCESSFULLY LOADED FONT '%s'(\"%s\")...\n", id.c_str(), fn.c_str());
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
		fprintf(stderr,"ERROR PARSING \'data.json\'!!!\nDETAILS:\n");
		fputs(err.what(),stderr);
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
		printf("PARSING TILE DATA...\n");
		json __ground_tiles = json_data["ground_tiles"];
		json __tiles = json_data["tiles"];
		for (json td : __ground_tiles)
			ground_tile_data[td[DATA_JSON_ID_KEY]] = td;
		for (json td : __tiles)
			tile_data[td["id"]] = td;
		printf("FOUND DATA FOR %d GROUND TILES...\n", ground_tile_data.size());
		int counter = 0;
		for (std::pair<std::string, json> pair : ground_tile_data)
		{
			printf("FOUND DATA FOR GROUND TILE \"%s\" (\"%s\")\n", ((std::string)pair.second[DATA_JSON_ID_KEY]).c_str(), ((std::string)pair.second[DATA_JSON_NAME_KEY]).c_str());
			gtile_ids_to_keys[counter] = pair.first;
			gtile_keys_to_ids[pair.first] = counter++;
		}
		counter = 0;
		printf("FOUND DATA FOR %d TILES...\n", tile_data.size());
		for (std::pair<std::string, json> pair : tile_data)
		{
			printf("FOUND DATA FOR TILE \"%s\" (\"%s\")\n", ((std::string)pair.second[DATA_JSON_ID_KEY]).c_str(), ((std::string)pair.second[DATA_JSON_NAME_KEY]).c_str());
			tile_ids_to_keys[counter] = pair.first;
			tile_keys_to_ids[pair.first] = counter++;
		}
		GrassGroundTile::Init(ground_tile_data[GrassGroundTile::ID]);
		DirtGroundTile::Init(ground_tile_data[DirtGroundTile::ID]);
		StoneGroundTile::Init(ground_tile_data[StoneGroundTile::ID]);
		SandGroundTile::Init(ground_tile_data[SandGroundTile::ID]);
		WaterGroundTile::Init(ground_tile_data[WaterGroundTile::ID]);
		MalachiteOreGroundTile::Init(ground_tile_data[MalachiteOreGroundTile::ID]);
		AzuriteOreGroundTile::Init(ground_tile_data[AzuriteOreGroundTile::ID]);
		HematiteOreGroundTile::Init(ground_tile_data[HematiteOreGroundTile::ID]);
		MagnetiteOreGroundTile::Init(ground_tile_data[MagnetiteOreGroundTile::ID]);
		prototype_gtiles[GrassGroundTile::ID] = new GrassGroundTile(nullptr, 0, 0);
		prototype_gtiles[DirtGroundTile::ID] = new DirtGroundTile(nullptr, 0, 0);
		prototype_gtiles[StoneGroundTile::ID] = new StoneGroundTile(nullptr, 0, 0);
		prototype_gtiles[SandGroundTile::ID] = new SandGroundTile(nullptr, 0, 0);
		prototype_gtiles[WaterGroundTile::ID] = new WaterGroundTile(nullptr, 0, 0);
		prototype_gtiles[MalachiteOreGroundTile::ID] = new MalachiteOreGroundTile(nullptr, 0, 0);
		prototype_gtiles[AzuriteOreGroundTile::ID] = new AzuriteOreGroundTile(nullptr, 0, 0);
		prototype_gtiles[HematiteOreGroundTile::ID] = new HematiteOreGroundTile(nullptr, 0, 0);
		prototype_gtiles[MagnetiteOreGroundTile::ID] = new MagnetiteOreGroundTile(nullptr, 0, 0);

		TreeTile::Init(tile_data[TreeTile::ID]);
		BerryBushTile::Init(tile_data[BerryBushTile::ID]);
		FenceTile::Init(tile_data[FenceTile::ID]);
		TorchTile::Init(tile_data[TorchTile::ID]);
		BurnerFurnaceMk1Tile::Init(tile_data[BurnerFurnaceMk1Tile::ID]);
		prototype_tiles[AirTile::ID] = new AirTile(nullptr, 0, 0);
		prototype_tiles[TreeTile::ID] = new TreeTile(nullptr, 0, 0);
		prototype_tiles[BerryBushTile::ID] = new BerryBushTile(nullptr, 0, 0);
		prototype_tiles[FenceTile::ID] = new FenceTile(nullptr, 0, 0);
		prototype_tiles[TorchTile::ID] = new TorchTile(nullptr, 0, 0);
		prototype_tiles[BurnerFurnaceMk1Tile::ID] = new BurnerFurnaceMk1Tile(nullptr, 0, 0);
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
		printf("PARSING ITEM DATA...\n");
		json __items = json_data["items"];
		json __loot_bundles = json_data["loot_bundles"];
		int counter = 0;
		for (json i : __items)
			item_data[i["id"]] = i;
		printf("LOADING %d ITEMS...\n", item_data.size());
		for (std::pair<std::string, json> pair : item_data)
		{
			printf("FOUND DATA FOR ITEM \"%s\" (\"%s\")\n", ((std::string)pair.second[DATA_JSON_ID_KEY]).c_str(), ((std::string)pair.second[DATA_JSON_NAME_KEY]).c_str());
			item_ids_to_keys[counter] = pair.first;
			item_keys_to_ids[pair.first] = counter++;
		}
		StoneItem::Init(item_data[StoneItem::ID]);
		DirtItem::Init(item_data[DirtItem::ID]);
		StickItem::Init(item_data[StickItem::ID]);
		SandItem::Init(item_data[SandItem::ID]);
		SimpleSword::Init(item_data[SimpleSword::ID]);
		GunItem::Init(item_data[GunItem::ID]);
		BerryItem::Init(item_data[BerryItem::ID]);
		AnthraciteCoalChunkItem::Init(item_data[AnthraciteCoalChunkItem::ID]);
		MalachiteChunkItem::Init(item_data[MalachiteChunkItem::ID]);
		MagnetiteChunkItem::Init(item_data[MagnetiteChunkItem::ID]);
		HematiteChunkItem::Init(item_data[HematiteChunkItem::ID]);
		AzuriteChunkItem::Init(item_data[AzuriteChunkItem::ID]);
		LodestoneItem::Init(item_data[LodestoneItem::ID]);
		SaplingItem::Init(item_data[SaplingItem::ID]);
		FenceItem::Init(item_data[FenceItem::ID]);
		TorchItem::Init(item_data[TorchItem::ID]);
		BurnerFurnaceMk1Item::Init(item_data[BurnerFurnaceMk1Item::ID]);

		prototype_items[StoneItem::ID] = new StoneItem();
		prototype_items[DirtItem::ID] = new DirtItem();
		prototype_items[StickItem::ID] = new StickItem();
		prototype_items[SandItem::ID] = new SandItem();
		prototype_items[SimpleSword::ID] = new SimpleSword();
		prototype_items[GunItem::ID] = new GunItem();
		prototype_items[BerryItem::ID] = new BerryItem();
		prototype_items[BurnerFurnaceMk1Item::ID] = new BurnerFurnaceMk1Item();
		prototype_items[AnthraciteCoalChunkItem::ID] = new AnthraciteCoalChunkItem();
		prototype_items[MalachiteChunkItem::ID] = new MalachiteChunkItem();
		prototype_items[MagnetiteChunkItem::ID] = new MagnetiteChunkItem();
		prototype_items[HematiteChunkItem::ID] = new HematiteChunkItem();
		prototype_items[AzuriteChunkItem::ID] = new AzuriteChunkItem();
		prototype_items[LodestoneItem::ID] = new LodestoneItem();
		prototype_items[SaplingItem::ID] = new SaplingItem();
		prototype_items[FenceItem::ID] = new FenceItem();
		prototype_items[TorchItem::ID] = new TorchItem();
		prototype_items[BurnerFurnaceMk1Item::ID] = new BurnerFurnaceMk1Item();
		printf("LOADING %d LOOT BUNDLES...\n", __loot_bundles.size());
		for (nlohmann::json data : __loot_bundles)
		{
			loaded_loot_bundles[data["id"]] = LootBundle::CreateFromJSON(data);
			printf("FOUND DATA FOR LOOT BUNDLE \"%s\"\n", ((std::string)data["id"]).c_str());
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

void init_quests()
{
	quest_collection = QuestCollection::MakeFromJSON(json_data["quests"]);
	for (const std::pair<std::string, Quest*>& p : quest_collection->quests)
		p.second->Resolve();
}

void init_entities()
{
	for (nlohmann::json j : json_data["entities"])
		entity_data[j["id"]] = j;
	int counter = 0;
	for (std::pair<std::string, json> pair : entity_data)
	{
		printf("FOUND DATA FOR ENTITY \"%s\" (\"%s\")\n", ((std::string)pair.second[DATA_JSON_ID_KEY]).c_str(), ((std::string)pair.second[DATA_JSON_NAME_KEY]).c_str());
		entity_ids_to_keys[counter] = pair.first;
		entity_keys_to_ids[pair.first] = counter++;
	}
	CactusBossEntity::Init(entity_data[CactusBossEntity::ID]);
	CactusBossEntity::RattleProjectile::Init(entity_data[CactusBossEntity::RattleProjectile::ID]);
	ZombieEntity::Init(entity_data[ZombieEntity::ID]);
	PlayerEntity::Init(entity_data[PlayerEntity::ID]);
	prototype_entities[CactusBossEntity::ID] = new CactusBossEntity(nullptr, 0.f, 0.f);
	prototype_entities[CactusBossEntity::RattleProjectile::ID] = new CactusBossEntity::RattleProjectile(nullptr, 0.f, 0.f);
	prototype_entities[ZombieEntity::ID] = new ZombieEntity(nullptr, 0.f, 0.f);
	prototype_entities[PlayerEntity::ID] = new PlayerEntity(nullptr, 0.f, 0.f);
	printf("SUCCESSFULLY INITIALIZED ENTITIES!\n");
}

void init_recipes()
{
	CraftingRecipe::LoadRecipes(json_data["recipes"]["crafting"]);
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
