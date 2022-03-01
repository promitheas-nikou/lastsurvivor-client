#include "ResourceLoader.h"
#include <allegro5/error.h>
#include <fstream>
#include <iostream>
#include <Windows.h>
#include "ItemBundle.h"
#include "GrassGroundTile.h"
#include "DirtGroundTile.h"
#include "StoneGroundTile.h"
#include "TreeTile.h"
#include "StoneItem.h"
#include "DirtItem.h"
#include "SimpleItemBundle.h"
#include <iostream>

const std::string DATA_JSON_TEXTURE_KEY = "texture";
const std::string DATA_JSON_TEXTURE_LIST_KEY = "textures";
const std::string DATA_JSON_MINING_RESISTANCE_KEY = "mining_resistance";
const std::string DATA_JSON_TOOL_TYPE_KEY = "tool_type";
const std::string DATA_JSON_NAME_KEY = "name";
const std::string DATA_JSON_DESCRIPTION_KEY = "description";
const std::string DATA_JSON_DROP_KEY = "drops";
const std::string DATA_JSON_ID_KEY = "id";

nlohmann::json json_data;

std::unordered_map<std::string, ALLEGRO_MOUSE_CURSOR*> loaded_cursors;
std::unordered_map<std::string, ALLEGRO_BITMAP*> loaded_bitmaps;
std::unordered_map<std::string, Shader*> loaded_shaders;
std::unordered_map<std::string, ItemBundle*> loaded_loot_bundles;
std::unordered_map<std::string, std::map<int, ALLEGRO_FONT*>> loaded_fonts;

using json = nlohmann::json;

std::unordered_map<std::string, json> ground_tile_data;
std::unordered_map<std::string, json> tile_data;
std::unordered_map<std::string, json> item_data;

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
			if ((loaded_bitmaps[id] = al_load_bitmap(filename.c_str())) == NULL)
				printf("\tFAILED TO LOAD TEXTURE #%d(\"%s\")...\n", id, filename.c_str());
			else
				printf("\tSUCCESSFULLY LOADED TEXTURE #%d(\"%s\")...\n", id, filename.c_str());
		}
		window_icon = loaded_bitmaps[(std::string)json_data["WINDOW_ICON"]];
		printf("WINDOW ICON IS TEXTURE #%d\n", (std::string)json_data["WINDOW_ICON"]);

		nlohmann::json fonts_data = json_data["fonts"];
		printf("\nLOADING %d FONT(S)...\n", fonts_data.size());

		for (nlohmann::json font : fonts_data)
		{
			std::string id = font["id"];
			std::string fn = font["font"];
			for (int i = 10; i <= 80; i++)
				loaded_fonts[id][i] = al_load_font(fn.c_str(), i, 0);
			printf("SUCCESSFULLY LOADED FONT #%d(%s)...\n", id, fn.c_str());
		}
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
	try {
		printf("PARSING TILE DATA...\n");
		json __ground_tiles = json_data["ground_tiles"];
		json __tiles = json_data["tiles"];
		for (json td : __ground_tiles)
			ground_tile_data[td[DATA_JSON_ID_KEY]] = td;
		for (json td : __tiles)
			tile_data[td["id"]] = td;
		printf("FOUND DATA FOR %d GROUND TILES...\n", ground_tile_data.size());
		for (std::pair<std::string, json> pair : ground_tile_data)
		{
			printf("FOUND DATA FOR GROUND TILE \"%s\" (\"%s\")\n", ((std::string)pair.second[DATA_JSON_ID_KEY]).c_str(), ((std::string)pair.second[DATA_JSON_NAME_KEY]).c_str());
		}
		printf("FOUND DATA FOR %d TILES...\n", tile_data.size());
		for (std::pair<std::string, json> pair : tile_data)
		{
			printf("FOUND DATA FOR TILE \"%s\" (\"%s\")\n", ((std::string)pair.second[DATA_JSON_ID_KEY]).c_str(), ((std::string)pair.second[DATA_JSON_NAME_KEY]).c_str());
		}
		GrassGroundTile::Init(ground_tile_data[GrassGroundTile::ID]);
		DirtGroundTile::Init(ground_tile_data[DirtGroundTile::ID]);
		StoneGroundTile::Init(ground_tile_data[StoneGroundTile::ID]);

		TreeTile::Init(tile_data[TreeTile::ID]);
	}
	catch (const nlohmann::json::type_error& err)
	{
		fprintf(stderr,"ERROR LOADING TILES!!!\nDETAILS:\n");
		fputs(err.what(), stderr);
		fprintf(stderr, "\n\nEXITING!!!\n");
		exit(EXIT_FAILURE);
	}
}

void init_items()
{
	try {
		printf("PARSING ITEM DATA...\n");
		json __items = json_data["items"];
		json __loot_bundles = json_data["loot_bundles"];
		for (json i : __items)
			item_data[i["id"]] = i;
		printf("LOADING %d ITEMS...\n", item_data.size());
		for (std::pair<std::string, json> pair : item_data)
		{
			printf("FOUND DATA FOR ITEM \"%s\" (\"%s\")\n", ((std::string)pair.second[DATA_JSON_ID_KEY]).c_str(), ((std::string)pair.second[DATA_JSON_NAME_KEY]).c_str());
		}
		StoneItem::Init(item_data[StoneItem::ID]);
		DirtItem::Init(item_data[DirtItem::ID]);
		printf("LOADING %d LOOT BUNDLES...\n", __loot_bundles.size());
		for (nlohmann::json data : __loot_bundles)
		{
			loaded_loot_bundles[data["id"]] = SimpleItemBundle::CreateFromJSON(data);
			printf("FOUND DATA FOR LOOT BUNDLE \"%s\"\n", ((std::string)data["id"]).c_str());
		}
	}
	catch (const nlohmann::json::type_error& err)
	{
		fprintf(stderr, "ERROR LOADING ITEMS!!!\nDETAILS:\n");
		fputs(err.what(), stderr);
		fprintf(stderr, "\n\nEXITING!!!\n");
		exit(EXIT_FAILURE);
	}
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
