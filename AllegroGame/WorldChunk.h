#pragma once
#include "GroundTile.h"
#include "Tile.h"


class World;

class WorldChunk
{
public:

	constexpr static int CHUNK_SIZE_X = 16;
	constexpr static int CHUNK_SIZE_Y = 16;
	constexpr static float CHUNK_SIZE_Xf = 16.f;
	constexpr static float CHUNK_SIZE_Yf = 16.f;

	void Tick();

	GroundTile* GetGroundTile(int x, int y) const;
	GroundTile* SetGroundTile(GroundTile* gtile, int x, int y);

	Tile* GetTile(int x, int y) const;
	Tile* SetTile(Tile* tile, int x, int y);
	Tile* RemoveTile(int x, int y);

	WorldChunk(World* w, int x, int y, bool generate = true);

	friend World;

private:
	World* world;

	GroundTile* ground_tiles[CHUNK_SIZE_Y][CHUNK_SIZE_X];
	Tile* tiles[CHUNK_SIZE_Y][CHUNK_SIZE_X];
	int chunkX, chunkY;

	void Generate();

};

