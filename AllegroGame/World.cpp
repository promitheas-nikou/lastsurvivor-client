#include "World.h"
#include "ResourceLoader.h"
#include "MathUtils.h"

void World::UpdateEntityVector()
{
    std::vector<Entity*> new_entities;
    for (int i = 0; i < entities.size(); i++)
        if (!entities[i]->shouldBeRemoved())
            new_entities.push_back(entities[i]);
    entityUpdates = 0;
    entities = new_entities;
}

Tile* World::GenerateTile(int x, int y)
{
    return MakeTile(((rand()%10)/9)+1, x, y);
}

WorldChunk* World::GetChunk(int x, int y)   
{
    return chunks[y][x];
}

void World::Tick()
{
    static int tick_counter=0;
    loadedChunkCount = 0;

    double BEGIN_TIME = al_get_time();
    for (const std::pair<int, std::map<int, WorldChunk*>> &m : chunks)
        for (const std::pair<int, WorldChunk*>& wc : m.second)
        {
            wc.second->Tick();
            loadedChunkCount++;
        }
    double END_TIME = al_get_time();
    printf("UPDATED %d CHUNKS IN %.3lf SECONDS\n", loadedChunkCount, END_TIME - BEGIN_TIME);

    if (tick_counter++ % ENTITY_UPDATE_RATE)
        UpdateEntityVector();
    
}

void World::GenerateChunk(int x, int y)
{
    //printf("Generating worldchunk %d:%d\n", x, y);
    chunks[y][x] = new WorldChunk(x, y);
}

Tile* World::GetTile(int x, int y)
{
    int subX = positive_modulo(x,16);
    int subY = positive_modulo(y,16);
    int chunkX = (x-subX) / CHUNK_SIZE_X;
    int chunkY = (y-subY) / CHUNK_SIZE_Y;
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

void World::Draw()
{
    loaded_shaders[1]->Use();
    int offset_x = player->getXpos() * 128;
    int offset_y = player->getYpos() * 128;
    int drawBeginX = floor(player->getXpos()) - 10;
    int drawEndX = drawBeginX + 20;
    int drawBeginY = floor(player->getYpos()) - 10;
    int drawEndY = drawBeginY + 20;
    al_build_transform(&draw_transform, -offset_x, -offset_y, 1, 1, 0);
    al_use_transform(&draw_transform);
    for (int x = drawBeginX; x < drawEndX; x++)
        for (int y = drawBeginY; y < drawEndY; y++)
            GetTile(x, y)->Draw();
    al_build_transform(&draw_transform, 0, 0, 1, 1, 0);
    al_use_transform(&draw_transform);
}

World::World(): dynamicWorldGen(false), entityUpdates(0), loadedChunkCount(0), player(new PlayerEntity())
{}


