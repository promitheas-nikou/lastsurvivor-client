#pragma once
#include "GroundTile.h"

#define CHUNK_SIZE_X (16)
#define CHUNK_SIZE_Y (16)
#define CHUNK_SIZE_Xf (16.f)
#define CHUNK_SIZE_Yf (16.f)

class WorldChunk
{
private:
	GroundTile* groundTiles[CHUNK_SIZE_Y][CHUNK_SIZE_X];
	int chunkX, chunkY;

	void Generate();

public:

	void Tick();

	GroundTile* GetTile(int x, int y);

	WorldChunk(int x, int y);

};

