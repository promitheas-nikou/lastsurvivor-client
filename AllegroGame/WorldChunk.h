#pragma once
#include "GroundTile.h"
#include "Tile.h"

#define CHUNK_SIZE_X (16)
#define CHUNK_SIZE_Y (16)
#define CHUNK_SIZE_Xf (16.f)
#define CHUNK_SIZE_Yf (16.f)

class WorldChunk
{
private:
	World* world;

	GroundTile* groundTiles[CHUNK_SIZE_Y][CHUNK_SIZE_X];
	Tile* tiles[CHUNK_SIZE_Y][CHUNK_SIZE_X];
	int chunkX, chunkY;

	void Generate();

public:

	void Tick();

	GroundTile* GetGroundTile(int x, int y) const;

	Tile* GetTile(int x, int y) const;
	void RemoveTile(int x, int y);

	WorldChunk(World* w, int x, int y);

};

