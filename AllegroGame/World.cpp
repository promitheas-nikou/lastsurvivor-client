#include <fstream>
#include "zip.h"
#include "json.h"
#include "World.h"
#include "ResourceLoader.h"
#include "Graphics.h"
#include "dirent.h"
#include "MathUtils.h"
#include "SimplexNoise.h"

#define DEBUG


#define WORLD_SAVE_MANIFEST_FILENAME "world_manifest.json"
#define WORLD_SAVE_MANIFEST_DYNAMIC_WORLDGEN_KEY "DO_DYNAMIC_WORLDGEN"
#define WORLD_SAVE_MANIFEST_SEED_KEY "SEED"
#define WORLD_SAVE_MANIFEST_VERSION_KEY "VERSION"
#define WORLD_SAVE_MANIFEST_VER_MAJOR_KEY "VER_MAJOR"
#define WORLD_SAVE_MANIFEST_VER_MINOR_KEY "VER_MINOR"
#define WORLD_SAVE_MANIFEST_NAME_KEY "NAME"
#define WORLD_SAVE_MANIFEST_CHUNKS_KEY "CHUNKS"
#define WORLD_SAVE_MANIFEST_TILES_DICT_KEY "TILES"
#define WORLD_SAVE_MANIFEST_GROUND_TILES_DICT_KEY "GTILES"
#define WORLD_SAVE_MANIFEST_ITEMS_DICT_KEY "ITEMS"
#define WORLD_SAVE_MANIFEST_CHUNK_X_SIZE_KEY "CHUNK_X_SIZE"
#define WORLD_SAVE_MANIFEST_CHUNK_Y_SIZE_KEY "CHUNK_Y_SIZE"
#define WORLD_SAVE_COORDINATE_DELIMETER "~"
#define WORLD_SAVE_CHUNKDATA_FILE_EXTENSION ".chunkdata"
#define WORLD_SAVE_CHUNKDATA_DIR "chunks"

void World::UpdateEntityVector()
{
    std::vector<Entity*> new_entities;
    for (int i = 0; i < entities.size(); i++)
        if (!entities[i]->shouldBeRemoved())
            new_entities.push_back(entities[i]);
    entityUpdates = 0;
    entities = new_entities;
}

GroundTile* World::GenerateGroundTile(int x, int y)
{
    if (GenerateGetLevelHeight(x, y) < .7)
    {
        if (GenerateGetLevelHeight(x, y) < -.4)
        {
            if (GenerateGetLevelHeight(x, y) < -.6)
            {
                return MakeGroundTile(this, "gtiles.water", x, y);
            }
            return MakeGroundTile(this, "gtiles.sand", x, y);
        }
        if (GenerateGetLevelTemperature(x, y) < .5)
        {
            if (GenerateGetLevelHumidity(x, y) < -.5)
                return MakeGroundTile(this, "gtiles.sand", x, y);
            else
                return MakeGroundTile(this, "gtiles.grass", x, y);
        }
        else
            return MakeGroundTile(this, "gtiles.dirt", x, y);
    }
    else
        return MakeGroundTile(this, "gtiles.stone", x, y);
}

float World::GenerateGetLevelHeight(int x, int y)
{
    return randgen.fractal(3, x / 20.f, y / 20.f);
}

float World::GenerateGetLevelTemperature(int x, int y)
{
    return randgen.fractal(3, x / 100.f-812, y / 100.f+752);
}

float World::GenerateGetLevelHumidity(int x, int y)
{
    return randgen.fractal(3,x/40.f+925,y/40.f-461);
}

Tile* World::GenerateTile(int x, int y)
{
    if ((GenerateGetLevelHeight(x, y) < .5)&&(GenerateGetLevelHeight(x, y) > -.3))
    {
        if (GenerateGetLevelTemperature(x, y) < .3)
        {
            if (GenerateGetLevelHumidity(x, y) < .3)
                return MakeTile(this, "tiles.air", x, y);
            else
                return MakeTile(this, "tiles.tree", x, y);
        }
        else
            return MakeTile(this, "tiles.air", x, y);
    }
    else
        return MakeTile(this, "tiles.air", x, y);
}

WorldChunk* World::GetChunk(int x, int y)   
{
    return chunks[y][x];
}

Tile* World::RemoveTile(int x, int y)
{
    int subX = positive_modulo(x, 16);
    int subY = positive_modulo(y, 16);
    int chunkX = (x - subX) / WorldChunk::CHUNK_SIZE_X;
    int chunkY = (y - subY) / WorldChunk::CHUNK_SIZE_Y;
    if (!IsChunkGenerated(chunkX, chunkY))
        GenerateChunk(chunkX, chunkY);
    return GetChunk(chunkX, chunkY)->RemoveTile(subX, subY);
}

void World::Tick()
{
    static int tick_counter=0;
    loadedChunkCount = 0;

    for (const std::pair<int, std::map<int, WorldChunk*>> &m : chunks)
        for (const std::pair<int, WorldChunk*>& wc : m.second)
        {
            wc.second->Tick();
            loadedChunkCount++;
        }

    for (Entity* const &e : entities)
        e->Tick();
    player->Tick();

    if ((tick_counter++ % ENTITY_UPDATE_RATE)!=0)
        UpdateEntityVector();
    
}

const PlayerEntity* World::GetPlayer() const
{
    return player;
}

void World::GenerateChunk(int x, int y)
{
    //printf("Generating worldchunk %d:%d\n", x, y);
    chunks[y][x] = new WorldChunk(this, x, y);
}

GroundTile* World::GetGroundTile(int x, int y)
{
    int subX = positive_modulo(x,16);
    int subY = positive_modulo(y,16);
    int chunkX = (x-subX) / WorldChunk::CHUNK_SIZE_X;
    int chunkY = (y-subY) / WorldChunk::CHUNK_SIZE_Y;
    if (!IsChunkGenerated(chunkX, chunkY))
        GenerateChunk(chunkX, chunkY);
    auto t = GetChunk(chunkX, chunkY)->GetGroundTile(subX, subY);
    return t;
}

GroundTile* World::SetGroundTile(GroundTile* gtile, int x, int y)
{
    int subX = positive_modulo(x, 16);
    int subY = positive_modulo(y, 16);
    int chunkX = (x - subX) / WorldChunk::CHUNK_SIZE_X;
    int chunkY = (y - subY) / WorldChunk::CHUNK_SIZE_Y;
    if (!IsChunkGenerated(chunkX, chunkY))
        GenerateChunk(chunkX, chunkY);
    return GetChunk(chunkX, chunkY)->SetGroundTile(gtile,subX, subY);
}

Tile* World::GetTile(int x, int y)
{
    int subX = positive_modulo(x, WorldChunk::CHUNK_SIZE_X);
    int subY = positive_modulo(y, WorldChunk::CHUNK_SIZE_Y);
    int chunkX = (x - subX) / WorldChunk::CHUNK_SIZE_X;
    int chunkY = (y - subY) / WorldChunk::CHUNK_SIZE_Y;
    if (!IsChunkGenerated(chunkX, chunkY))
        GenerateChunk(chunkX, chunkY);
    auto t = GetChunk(chunkX, chunkY)->GetTile(subX, subY);
    return t;
}

Tile* World::SetTile(Tile* tile, int x, int y)
{
    int subX = positive_modulo(x, 16);
    int subY = positive_modulo(y, 16);
    int chunkX = (x - subX) / WorldChunk::CHUNK_SIZE_X;
    int chunkY = (y - subY) / WorldChunk::CHUNK_SIZE_Y;
    if (!IsChunkGenerated(chunkX, chunkY))
        GenerateChunk(chunkX, chunkY);
    return GetChunk(chunkX, chunkY)->SetTile(tile, subX, subY);
}

bool World::IsChunkGenerated(int x, int y)
{
    auto row = chunks.find(y);
    if (row == chunks.end())
        return false;
    return chunks[y].find(x) != chunks[y].end();
}

ALLEGRO_TRANSFORM draw_transform;

int OPTION_DRAW_TILES_LEFT = 12;
int OPTION_DRAW_TILES_RIGHT = 12;
int OPTION_DRAW_TILES_UP = 7;
int OPTION_DRAW_TILES_DOWN = 7;

void World::Draw()
{
    //DRAW TILES
    loaded_shaders["world"]->Use();
    int offset_x = floor(player->GetXpos() * 128) - SCREEN_WIDTH / 2;
    int offset_y = floor(player->GetYpos() * 128) - SCREEN_HEIGHT / 2;
    int drawBeginX = floor(player->GetXpos()) - OPTION_DRAW_TILES_LEFT;
    int drawEndX = floor(player->GetXpos()) + OPTION_DRAW_TILES_RIGHT;
    int drawBeginY = floor(player->GetYpos()) - OPTION_DRAW_TILES_UP;
    int drawEndY = floor(player->GetYpos()) + OPTION_DRAW_TILES_DOWN;
    al_build_transform(&draw_transform, -offset_x, -offset_y, 1, 1, 0);
    al_use_transform(&draw_transform);
    for (int x = drawBeginX; x < drawEndX; x++)
        for (int y = drawBeginY; y < drawEndY; y++)
            GetGroundTile(x, y)->Draw();
    for (int x = drawBeginX; x < drawEndX; x++)
        for (int y = drawBeginY; y < drawEndY; y++)
            GetTile(x, y)->Draw();

    for (Entity* e : entities)
        e->Tick();

    //DRAW ENTITIES
    for (Entity* e : entities)
        //if(!e->shouldBeRemoved())
            e->Draw();
    player->Draw();
    al_build_transform(&draw_transform, 0, 0, 1, 1, 0);
    al_use_transform(&draw_transform);
}

//int OnWorldArchiveFileExtract() {}

#include <iostream>

World* World::LoadWorldFromFile(std::string filename)
{
    std::filesystem::path dir = std::filesystem::temp_directory_path() / "LastSurvivorTemp";
    World* world = nullptr;
#ifndef DEBUG
    try
    {
#endif //DEBUG
        zip_extract(filename.c_str(), dir.string().c_str(), NULL, NULL);
        nlohmann::json manifest = nlohmann::json::parse(std::ifstream(dir / WORLD_SAVE_MANIFEST_FILENAME));

        std::cout << manifest;

        std::cout << manifest[WORLD_SAVE_MANIFEST_SEED_KEY];
        world = new World(
            manifest[WORLD_SAVE_MANIFEST_DYNAMIC_WORLDGEN_KEY],
            manifest[WORLD_SAVE_MANIFEST_SEED_KEY],
            manifest[WORLD_SAVE_MANIFEST_NAME_KEY],
            manifest[WORLD_SAVE_MANIFEST_VERSION_KEY],
            manifest[WORLD_SAVE_MANIFEST_VER_MAJOR_KEY],
            manifest[WORLD_SAVE_MANIFEST_VER_MINOR_KEY]);

        if ((manifest[WORLD_SAVE_MANIFEST_CHUNK_X_SIZE_KEY] != WorldChunk::CHUNK_SIZE_X) || (manifest[WORLD_SAVE_MANIFEST_CHUNK_Y_SIZE_KEY] != WorldChunk::CHUNK_SIZE_Y))
            throw std::format_error("WORLD FILE HAS DIFFERENT CHUNK SIZE!!!");
        std::map<uint32_t, std::string> cur_tile_keys;
        std::map<uint32_t, std::string> cur_gtile_keys;
        std::map<uint32_t, std::string> cur_item_ids;

        for (auto& [key, value] : manifest[WORLD_SAVE_MANIFEST_TILES_DICT_KEY].items())
            cur_tile_keys[std::stoi(key)] = value;
        for (auto& [key, value] : manifest[WORLD_SAVE_MANIFEST_GROUND_TILES_DICT_KEY].items())
            cur_gtile_keys[std::stoi(key)] = value;
        for (auto& [key, value] : manifest[WORLD_SAVE_MANIFEST_ITEMS_DICT_KEY].items())
            cur_item_ids[std::stoi(key)] = value;

        for (auto& [key, value] : manifest[WORLD_SAVE_MANIFEST_CHUNKS_KEY].items())
        {
            int pos = key.find(WORLD_SAVE_COORDINATE_DELIMETER);
            int cx = std::stoi(key.substr(0, pos));
            int cy = std::stoi(key.substr(pos+1));
            WorldChunk* chunk = new WorldChunk(world, cx, cy, false);

            std::ifstream chunkdata = std::ifstream(dir / WORLD_SAVE_CHUNKDATA_DIR / (std::string)value);

            for (int y = 0; y < WorldChunk::CHUNK_SIZE_Y; y++)
                for (int x = 0; x < WorldChunk::CHUNK_SIZE_X; x++)
                {
                    uint32_t gtileid,tileid;
                    chunkdata.read(reinterpret_cast<char*>(&gtileid), sizeof(uint32_t));
                    chunk->ground_tiles[y][x] = MakeGroundTile(world, cur_gtile_keys[gtileid], cx * WorldChunk::CHUNK_SIZE_Y + x, cy * WorldChunk::CHUNK_SIZE_X + y);
                    chunk->ground_tiles[y][x]->LoadAdditionalDataFromFile(chunkdata);
                    chunkdata.read(reinterpret_cast<char*>(&tileid), sizeof(uint32_t));
                    chunk->tiles[y][x] = MakeTile(world, cur_tile_keys[gtileid], cx * WorldChunk::CHUNK_SIZE_Y + x, cy * WorldChunk::CHUNK_SIZE_X + y);
                    chunk->tiles[y][x]->LoadAdditionalDataFromFile(chunkdata);
                }
            world->chunks[cx][cy] = chunk;
        }
#ifndef DEBUG
    }
    catch (std::exception e)
    {
        printf("ERROR LOADING WORLD FROM FILE \"%s\"!\nDETAILS:\n%s\n", filename.c_str(),e.what());
        
        if (world != nullptr)
            delete world;
        world = nullptr;
    }
#endif //DEBUG
    try
    {
        //std::filesystem::remove_all(dir);
    }
    catch (std::filesystem::filesystem_error e) {}
    return world; 
}

int begin_filename_index;

void zip_walk(struct zip_t* zip, const char* path) {
    DIR* dir;
    struct dirent* entry;
    char fullpath[MAX_PATH];
    struct stat s;

    memset(fullpath, 0, MAX_PATH);
    dir = opendir(path);
    assert(dir);

    while ((entry = readdir(dir))) {
        // skip "." and ".."
        if (!strcmp(entry->d_name, ".\0") || !strcmp(entry->d_name, "..\0"))
            continue;

        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
        stat(fullpath, &s);
        if (S_ISDIR(s.st_mode))
            zip_walk(zip, fullpath);
        else {
            zip_entry_open(zip, fullpath+begin_filename_index);
            zip_entry_fwrite(zip, fullpath);
            zip_entry_close(zip);
        }
    }

    closedir(dir);
}

void World::SaveToFile(std::string filename)
{
    std::filesystem::path dir = std::filesystem::temp_directory_path() / "LastSurvivorTemp";
    std::cout << dir;
    std::ofstream manif_file(dir / WORLD_SAVE_MANIFEST_FILENAME);
    nlohmann::json manifest;
    manifest[WORLD_SAVE_MANIFEST_NAME_KEY] = worldname;
    manifest[WORLD_SAVE_MANIFEST_CHUNK_X_SIZE_KEY] = WorldChunk::CHUNK_SIZE_X;
    manifest[WORLD_SAVE_MANIFEST_CHUNK_Y_SIZE_KEY] = WorldChunk::CHUNK_SIZE_Y;
    manifest[WORLD_SAVE_MANIFEST_VERSION_KEY] = game_version_name;
    manifest[WORLD_SAVE_MANIFEST_VER_MAJOR_KEY] = game_version_major;
    manifest[WORLD_SAVE_MANIFEST_VER_MINOR_KEY] = game_version_minor;
    manifest[WORLD_SAVE_MANIFEST_DYNAMIC_WORLDGEN_KEY] = doDynamicWorldGen;
    manifest[WORLD_SAVE_MANIFEST_SEED_KEY] = SEED;
    for (const std::pair<int, std::string>& p : item_ids_to_keys)
        manifest[WORLD_SAVE_MANIFEST_ITEMS_DICT_KEY][p.first] = p.second;
    for (const std::pair<int, std::string>& p : tile_ids_to_keys)
        manifest[WORLD_SAVE_MANIFEST_TILES_DICT_KEY][p.first] = p.second;
    for (const std::pair<int, std::string>& p : gtile_ids_to_keys)
        manifest[WORLD_SAVE_MANIFEST_GROUND_TILES_DICT_KEY][p.first] = p.second;
    manif_file << manifest;
    manif_file.close();
    for(const std::pair<int,std::map<int,WorldChunk*>>& p1: chunks)
        for (const std::pair<int, WorldChunk*>& p2 : p1.second)
        {
            std::string key = std::format("{}" WORLD_SAVE_COORDINATE_DELIMETER "{}", p1.first, p2.first);
            std::string filename = key + WORLD_SAVE_CHUNKDATA_FILE_EXTENSION;
            manifest[WORLD_SAVE_MANIFEST_CHUNKS_KEY][key] = filename;
            std::filesystem::path chunkdatadir = dir / WORLD_SAVE_CHUNKDATA_DIR;
            std::filesystem::create_directory(chunkdatadir);
            std::ofstream chunkdata(chunkdatadir / filename);
            for (int y = 0; y < WorldChunk::CHUNK_SIZE_Y; y++)
                for (int x = 0; x < WorldChunk::CHUNK_SIZE_X; x++)
                {
                    GroundTile* gt = p2.second->ground_tiles[y][x];
                    chunkdata.write(reinterpret_cast<char*>(&gtile_keys_to_ids[gt->GetID()]), sizeof(uint32_t));
                    gt->WriteAdditionalDataToFile(chunkdata);
                    Tile* t = p2.second->tiles[y][x];
                    chunkdata.write(reinterpret_cast<char*>(&tile_keys_to_ids[t->GetID()]), sizeof(uint32_t));
                    t->WriteAdditionalDataToFile(chunkdata);
                }
            chunkdata.close();
        }
    zip_t* z = zip_open(filename.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
    if (z == NULL)
    {
        std::cerr << "ERROR SAVING WORLD!!!\n";
        //std::cerr << mz_lat
        return;
    }
    begin_filename_index = dir.string().size()+1;
    zip_walk(z, dir.string().c_str());
    zip_close(z);
}

World* World::CreateNewWorld(std::string name)
{
    srand((unsigned int)time(NULL));
    int a = abs(rand()*rand()*rand());
    printf("SEED: %d\n", a);
    return new World(true, a, name, game_version_name, game_version_minor, game_version_major);
}


World::World(bool w, const uint64_t s, std::string name, std::string n, int min, int maj) : doDynamicWorldGen(w), entityUpdates{ 0 }, loadedChunkCount{ 0 }, SEED{ s }, WorldGameVersionName{ n }, WorldGameVersionMinor{ min }, WorldGameVersionMajor{ maj }, worldname{ name }
{
    srand(s);
    float a = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2.f));
    float b = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2.f));
    float c = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2.f));
    float d = 1/c;

    std::cout << a << '\n' << b << '\n' << c << '\n' << d << '\n';
    randgen = SimplexNoise::SimplexNoise(a, b, c, d);
    player = new PlayerEntity(this, 0, 0);
}


