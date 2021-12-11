#include "World.h"
#include "MathUtils.h"

void World::RefreshEntityVector()
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
    return MakeTile(1, x, y);
}

WorldChunk* World::GetChunk(int x, int y)
{
    return chunks[y][x];
}

void World::GenerateChunk(int x, int y)
{
    //printf("Generating worldchunk %d:%d\n", x, y);
    chunks[y][x] = new WorldChunk(x, y);
}

Tile* World::GetTile(int x, int y)
{
    int xdif = (x < 0)*16;
    int ydif = (y < 0)*16;
    int chunkX = util_floor(x / CHUNK_SIZE_Xf);
    int chunkY = util_floor(y / CHUNK_SIZE_Yf);
    if (!IsChunkGenerated(chunkX, chunkY))
        GenerateChunk(chunkX, chunkY);
    return GetChunk(util_floor(x / CHUNK_SIZE_Xf), util_floor(y / CHUNK_SIZE_Yf))->GetTile(x % CHUNK_SIZE_X + xdif, y % CHUNK_SIZE_Y + ydif);
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
    player->xpos+=.01;
}

World::World()
{
    player = new PlayerEntity();
}


