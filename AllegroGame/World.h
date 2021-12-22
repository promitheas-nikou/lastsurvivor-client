#pragma once

#include "WorldChunk.h"
#include "Entity.h"
#include "PlayerEntity.h"
#include <vector>
#include <map>

class World
{
private:
	const static int ENTITY_UPDATE_RATE = 5;
	bool dynamicWorldGen;
	std::map<int, std::map<int, WorldChunk*>> chunks;

	static const float entityUpdatesUntilRefresh;
	int entityUpdates;
	std::vector<Entity*> entities;

	int loadedChunkCount;

	void UpdateEntityVector();

	PlayerEntity* player;

	static GroundTile* GenerateGroundTile(int x, int y);

public:
	inline WorldChunk* GetChunk(int x, int y);

	void Tick();

	void GenerateChunk(int x, int y);

	GroundTile* GetTile(int x, int y);

	bool IsChunkGenerated(int x, int y);

	void Draw();

	World();

	friend WorldChunk;
	friend int main();
};

