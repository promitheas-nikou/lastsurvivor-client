#include "World.h"
#include "ResourceLoader.h"
#include "Graphics.h"
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

GroundTile* World::GenerateGroundTile(int x, int y)
{
    return MakeGroundTile(this, ((rand()%10)/9)+1, x, y);
}

Tile* World::GenerateTile(int x, int y)
{
    return MakeTile(this, 0, x, y);
}

WorldChunk* World::GetChunk(int x, int y)   
{
    return chunks[y][x];
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
    int subX = positive_modulo(x, 16);
    int subY = positive_modulo(y, 16);
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

void World::Draw()
{
    //DRAW TILES
    loaded_shaders[1]->Use();
    int offset_x = floor(player->getXpos() * 128) - SCREEN_WIDTH / 2;
    int offset_y = floor(player->getYpos() * 128) - SCREEN_HEIGHT / 2;
    int drawBeginX = floor(player->getXpos()) - 10;
    int drawEndX = drawBeginX + 20;
    int drawBeginY = floor(player->getYpos()) - 10;
    int drawEndY = drawBeginY + 20;
    al_build_transform(&draw_transform, -offset_x, -offset_y, 1, 1, 0);
    al_use_transform(&draw_transform);
    for (int x = drawBeginX; x < drawEndX; x++)
        for (int y = drawBeginY; y < drawEndY; y++)
            GetGroundTile(x, y)->Draw();
    for (int x = drawBeginX; x < drawEndX; x++)
        for (int y = drawBeginY; y < drawEndY; y++)
            GetTile(x, y)->Draw();

    //DRAW ENTITIES
    for (Entity* e : entities)
        //if(!e->shouldBeRemoved())
            e->Draw();
    player->Draw();
    al_build_transform(&draw_transform, 0, 0, 1, 1, 0);
    al_use_transform(&draw_transform);
}

World::World(): dynamicWorldGen(false), entityUpdates(0), loadedChunkCount(0), player(new PlayerEntity(this)), SEED(0)
{}


