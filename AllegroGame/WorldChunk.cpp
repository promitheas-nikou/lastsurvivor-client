#include "WorldChunk.h"
#include "World.h"
#define _WORLD_CHUNK_TILE_PTR(x,y) (tiles[y*CHUNK_SIZE_Y+x])
#define _WORLD_CHUNK_GTILE_PTR(x,y) (ground_tiles[y*CHUNK_SIZE_Y+x])

void WorldChunk::Generate()
{
    int tmpx, tmpy;
    for (int y = 0; y < CHUNK_SIZE_Y; y++)
        for (int x = 0; x < CHUNK_SIZE_X; x++)
        {
            tmpx = CHUNK_SIZE_X * chunkX + x;
            tmpy = CHUNK_SIZE_Y * chunkY + y;
            _WORLD_CHUNK_GTILE_PTR(x,y) = world->GenerateGroundTile(tmpx, tmpy);
            _WORLD_CHUNK_TILE_PTR(x,y) = world->GenerateTile(tmpx, tmpy);
        }
}

void WorldChunk::Tick()
{
    for (Tile* t : tickingTiles)
        t->TickUpdate(world->GetGameTimeAbsolute());
    _WORLD_CHUNK_TILE_PTR(rand() % CHUNK_SIZE_X, rand() % CHUNK_SIZE_Y)->RandomTickUpdate();
}

GroundTile*& WorldChunk::GetGroundTileRef(int x, int y)
{
    return _WORLD_CHUNK_GTILE_PTR(x,y);
}

GroundTile* WorldChunk::GetGroundTile(int x, int y) const
{
    return _WORLD_CHUNK_GTILE_PTR(x, y);
}

GroundTile* WorldChunk::SetGroundTile(GroundTile* gtile, int x, int y)
{
    GroundTile* tmp = _WORLD_CHUNK_GTILE_PTR(x,y);
    _WORLD_CHUNK_GTILE_PTR(x, y) = gtile;
    return tmp;
}

Tile* WorldChunk::GetTile(int x, int y) const
{
    return _WORLD_CHUNK_TILE_PTR(x, y);
}

Tile*& WorldChunk::GetTileRef(int x, int y)
{
    return _WORLD_CHUNK_TILE_PTR(x, y);
}

Tile* WorldChunk::SetTile(Tile* tile, int x, int y)
{
    Tile* tmp = _WORLD_CHUNK_TILE_PTR(x, y);
    _WORLD_CHUNK_TILE_PTR(x, y) = tile;
    return tmp;
}

Tile* WorldChunk::RemoveTile(int x, int y)
{
    Tile* tmp = _WORLD_CHUNK_TILE_PTR(x, y);
    _WORLD_CHUNK_TILE_PTR(x, y) = MakeTile(world, "tiles.air", x, y);
    return tmp;
}

void WorldChunk::AddTickingTile(Tile* t)
{
    tickingTiles.insert(t);
}

void WorldChunk::RemoveTickingTile(Tile* t)
{
    tickingTiles.erase(t);
}

WorldChunk::WorldChunk(World* w, int x, int y, bool generate): world(w), chunkX(x), chunkY(y)
{
    if(generate)
        Generate();
}

