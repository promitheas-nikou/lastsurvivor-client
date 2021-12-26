#include "ResourceLoader.h"
#include <allegro5/error.h>
#include <fstream>
#include <iostream>
#include <Windows.h>
#include "GrassGroundTile.h"
#include "DirtGroundTile.h"
#include "StoneGroundTile.h"

nlohmann::json json_data;

std::map<int, ALLEGRO_MOUSE_CURSOR*> loaded_cursors;
std::map<int, ALLEGRO_BITMAP*> loaded_bitmaps;
std::map<int, Shader*> loaded_shaders;
std::map<int, std::map<int, ALLEGRO_FONT*>> loaded_fonts;

using json = nlohmann::json;

std::map<int, json> tile_data;

std::string game_name;
std::string game_version_name;
int game_version_major;
int game_version_minor;

ALLEGRO_BITMAP* window_icon;

void load_resources()
{
	json_data = json::parse(std::ifstream("data.json"));

	game_name = json_data["NAME"];
	game_version_name = json_data["VERSION"];

	json textures = json_data["textures"];
	
	printf("CURRENT DIRECTORY: \"%s\"\n\n", al_get_current_directory());

	printf("LOADING %d TEXTURE(S):\n", textures.size());

	for (json texture_data : textures)
	{
		int id = texture_data["id"];
		std::string filename = texture_data["filename"];
		if ((loaded_bitmaps[id] = al_load_bitmap(filename.c_str())) == NULL)
			printf("\tFAILED TO LOAD TEXTURE #%d(\"%s\")...\n", id, filename.c_str());
		else
			printf("\tSUCCESSFULLY LOADED TEXTURE #%d(\"%s\")...\n", id, filename.c_str());
	}
	window_icon = loaded_bitmaps[(int)json_data["WINDOW_ICON"]];
	printf("WINDOW ICON IS TEXTURE #%d\n", (int)json_data["WINDOW_ICON"]);

	nlohmann::json fonts_data = json_data["fonts"];
	printf("\nLOADING %d FONT(S)...\n", fonts_data.size());

	for (nlohmann::json font : fonts_data)
	{
		int id = font["id"];
		std::string fn = font["font"];
		printf("LOADING FONT #%d\n", id);
		for(int i=10;i<=80;i++)
			loaded_fonts[id][i] = al_load_font(fn.c_str(), i, 0);
	}

}

void load_shaders()
{
	json shaders = json_data["shaders"];

	loaded_shaders[0] = new Shader(0);

	for (json texture_data : shaders)
	{
		int id = texture_data["id"];
		std::string vertex = texture_data["vertex"];
		std::string fragment = texture_data["fragment"];
		loaded_shaders[id] = new Shader(id, vertex.c_str(), fragment.c_str());
	}

}

void init_tiles()
{
	printf("PARSING TILE DATA...\n");
	json __ground_tiles = json_data["ground_tiles"];
	for (json td : __ground_tiles)
		tile_data[td["id"]] = td;
	printf("LOADING %d TILES...\n", tile_data.size());
	for (std::pair<int, json> pair : tile_data)
	{
		printf("LOADED TILE #%d (\"%s\")\n",pair.first, ((std::string)pair.second["name"]).c_str());
	}
	GrassGroundTile::Init(tile_data[GrassGroundTile::ID]);
	DirtGroundTile::Init(tile_data[DirtGroundTile::ID]);
	StoneGroundTile::Init(tile_data[StoneGroundTile::ID]);
}

void free_resources()
{
	for (std::pair<int, ALLEGRO_BITMAP*> p : loaded_bitmaps)
		al_destroy_bitmap(p.second);
	loaded_bitmaps.clear();
	window_icon = NULL;
	for (std::pair<int, ALLEGRO_MOUSE_CURSOR*> p : loaded_cursors)
		al_destroy_mouse_cursor(p.second);
	loaded_cursors.clear();
	for(auto m: loaded_fonts)
		for(auto f: m.second)
			al_destroy_font(f.second);
	loaded_fonts.clear();
	for (std::pair<int, Shader*> p : loaded_shaders)
	{
		p.second->Delete();
		delete p.second;
	}
}
