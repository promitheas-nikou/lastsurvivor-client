#include <fstream>
#include "zip.h"
#include "World.h"
#include "ResourceLoader.h"
#include "Graphics.h"
#include "MathUtils.h"
#include "SimplexNoise.h"

#define WORLD_MANIFEST_VERSION_KEY "VERSION"
#define WORLD_MANIFEST_VER_MAJOR_KEY "VER_MAJOR"
#define WORLD_MANIFEST_VER_MINOR_KEY "VER_MINOR"
#define WORLD_MANIFEST_NAME_KEY "NAME"

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
    if (GenerateGetLevelHight(x, y) < .9)
    {
        if (GenerateGetLevelTemperature(x, y) < 0)
        {   
            if (GenerateGetLevelHumidity(x, y) < -.4)
                return MakeGroundTile(this, "gtiles.dirt", x, y);
            else
                return MakeGroundTile(this, "gtiles.grass", x, y);
        }
        else
            return MakeGroundTile(this, "gtiles.dirt", x, y);
    }
    else
        return MakeGroundTile(this, "gtiles.stone", x, y);
}

float World::GenerateGetLevelHight(int x, int y)
{
    return SimplexNoise::noise(x / 20.f, y / 20.f);
}

float World::GenerateGetLevelTemperature(int x, int y)
{
    return SimplexNoise::noise(x / 100.f-812, y / 100.f+752);
}

float World::GenerateGetLevelHumidity(int x, int y)
{
    return SimplexNoise::noise(x/40.f+925,y/40.f-461);
}

Tile* World::GenerateTile(int x, int y)
{
    if (GenerateGetLevelHight(x, y) < 0)
    {
        if (GenerateGetLevelTemperature(x, y) < 0)
        {
            if (GenerateGetLevelHumidity(x, y) < 0)
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
    int chunkX = (x - subX) / CHUNK_SIZE_X;
    int chunkY = (y - subY) / CHUNK_SIZE_Y;
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
    int chunkX = (x-subX) / CHUNK_SIZE_X;
    int chunkY = (y-subY) / CHUNK_SIZE_Y;
    if (!IsChunkGenerated(chunkX, chunkY))
        GenerateChunk(chunkX, chunkY);
    auto t = GetChunk(chunkX, chunkY)->GetGroundTile(subX, subY);
    return t;
}

Tile* World::GetTile(int x, int y)
{
    int subX = positive_modulo(x, CHUNK_SIZE_X);
    int subY = positive_modulo(y, CHUNK_SIZE_Y);
    int chunkX = (x - subX) / CHUNK_SIZE_X;
    int chunkY = (y - subY) / CHUNK_SIZE_Y;
    if (!IsChunkGenerated(chunkX, chunkY))
        GenerateChunk(chunkX, chunkY);
    auto t = GetChunk(chunkX, chunkY)->GetTile(subX, subY);
    return t;
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

void LoadWorldManifest();

World* World::LoadWorldFromFile(std::string filename)
{
    std::filesystem::path dir = std::filesystem::temp_directory_path();
    std::string dir_name { dir.string() };
    zip_extract(filename.c_str(), dir_name.c_str(), NULL, NULL);
    

    return nullptr; 
}

void World::SaveToFile(std::string filename)
{
}


World::World() : doDynamicWorldGen(false), entityUpdates{ 0 }, loadedChunkCount{ 0 }, SEED{ 0 }
{
    player = new PlayerEntity(this, 0, 0);
}


