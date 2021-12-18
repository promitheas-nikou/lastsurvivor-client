#include "WorldChunk.h"
#include "World.h"

void WorldChunk::Generate()
{
    for (int y = 0; y < CHUNK_SIZE_Y; y++)
        for (int x = 0; x < CHUNK_SIZE_X; x++)
            tiles[y][x] = World::GenerateTile(CHUNK_SIZE_X * chunkX + x, CHUNK_SIZE_Y * chunkY + y);
}

void WorldChunk::Tick()
{
    for (int y = 0; y < CHUNK_SIZE_Y; y++)
        for (int x = 0; x < CHUNK_SIZE_X; x++)
            tiles[y][x]->TickUpdate();
}

Tile* WorldChunk::GetTile(int x, int y)
{
    return tiles[y][x];
}

WorldChunk::WorldChunk(int x, int y): chunkX(x), chunkY(y)
{
    Generate();
}

