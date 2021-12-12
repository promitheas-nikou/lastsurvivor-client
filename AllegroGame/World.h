#pragma once

#include "WorldChunk.h"
#include "Entity.h"
#include "PlayerEntity.h"
#include <vector>
#include <map>

class World
{
private:
	bool dynamicWorldGen;
	std::map<int, std::map<int, WorldChunk*>> chunks;

	static const float entityUpdatesUntilRefresh;
	int entityUpdates;
	std::vector<Entity*> entities;

	void RefreshEntityVector();

	PlayerEntity* player;

	static Tile* GenerateTile(int x, int y);
public:
	inline WorldChunk* GetChunk(int x, int y);

	void GenerateChunk(int x, int y);

	Tile* GetTile(int x, int y);

	bool IsChunkGenerated(int x, int y);

	void Draw();

	World();

	friend WorldChunk;
	friend int main();
};

