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
            ground_tiles[y][x] = world->GenerateGroundTile(tmpx, tmpy);
            tiles[y][x] = world->GenerateTile(tmpx, tmpy);
        }
}

void WorldChunk::Tick()
{
    for (int y = 0; y < CHUNK_SIZE_Y; y++)
        for (int x = 0; x < CHUNK_SIZE_X; x++)
        {
            ground_tiles[y][x]->TickUpdate();
            tiles[y][x]->TickUpdate();
        }
    tiles[rand() % CHUNK_SIZE_X][rand() % CHUNK_SIZE_Y]->RandomTickUpdate();
}

GroundTile* WorldChunk::GetGroundTile(int x, int y) const
{
    return ground_tiles[y][x];
}

GroundTile* WorldChunk::SetGroundTile(GroundTile* gtile, int x, int y)
{
    GroundTile* tmp = ground_tiles[y][x];
    ground_tiles[y][x] = gtile;
    return tmp;
}

Tile* WorldChunk::GetTile(int x, int y) const
{
    return tiles[y][x];
}

Tile* WorldChunk::SetTile(Tile* tile, int x, int y)
{
    Tile* tmp = tiles[y][x];
    tiles[y][x] = tile;
    return tmp;
}

Tile* WorldChunk::RemoveTile(int x, int y)
{
    Tile* tmp = tiles[y][x];
    tiles[y][x] = MakeTile(world, "tiles.air", x, y);
    return tmp;
}

WorldChunk::WorldChunk(World* w, int x, int y, bool generate): world(w), chunkX(x), chunkY(y)
{
    if(generate)
        Generate();
}

