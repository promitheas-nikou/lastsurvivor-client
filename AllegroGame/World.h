#pragma once

#include "WorldChunk.h"
#include "Entity.h"
#include "PlayerEntity.h"
#include "GroundTile.h"
#include "Tile.h"
#include <vector>
#include <map>

class World
{
private:
	const uint64_t SEED;
	const static int ENTITY_UPDATE_RATE = 5; //HOW MANY TICKS BEFORE CALLING `UpdateEntityVector()`
	bool dynamicWorldGen;
	std::map<int, std::map<int, WorldChunk*>> chunks;

	static const float entityUpdatesUntilRefresh;
	int entityUpdates;
	std::vector<Entity*> entities;

	int loadedChunkCount;

	void UpdateEntityVector();

	PlayerEntity* player;

	GroundTile* GenerateGroundTile(int x, int y);

	Tile* GenerateTile(int x, int y);

public:
	inline WorldChunk* GetChunk(int x, int y);

	void RemoveTile(int x, int y);

	void Tick();

	void GenerateChunk(int x, int y);

	GroundTile* GetGroundTile(int x, int y);

	Tile* GetTile(int x, int y);

	bool IsChunkGenerated(int x, int y);

	void Draw();

	World();

	friend WorldChunk;
	friend int main();
};

