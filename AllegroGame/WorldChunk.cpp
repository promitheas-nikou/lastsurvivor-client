#include "WorldChunk.h"
#include "World.h"

void WorldChunk::Generate()
{
    int tmpx, tmpy;
    for (int y = 0; y < CHUNK_SIZE_Y; y++)
        for (int x = 0; x < CHUNK_SIZE_X; x++)
        {
            tmpx = CHUNK_SIZE_X * chunkX + x;
            tmpy = CHUNK_SIZE_Y * chunkY + y;
            groundTiles[y][x] = world->GenerateGroundTile(tmpx, tmpy);
            tiles[y][x] = world->GenerateTile(tmpx, tmpy);
        }
}

void WorldChunk::Tick()
{
    for (int y = 0; y < CHUNK_SIZE_Y; y++)
        for (int x = 0; x < CHUNK_SIZE_X; x++)
            groundTiles[y][x]->TickUpdate();
}

GroundTile* WorldChunk::GetGroundTile(int x, int y) const
{
    return groundTiles[y][x];
}

Tile* WorldChunk::GetTile(int x, int y) const
{
    return tiles[y][x];
}

void WorldChunk::RemoveTile(int x, int y)
{
    tiles[y][x] = MakeTile(world, 0, x, y);
}

WorldChunk::WorldChunk(World* w, int x, int y): world(w), chunkX(x), chunkY(y)
{
    Generate();
}

