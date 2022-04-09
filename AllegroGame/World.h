#pragma once

#include "WorldChunk.h"
#include "Entity.h"
#include "PlayerEntity.h"
#include "GroundTile.h"
#include "Tile.h"
#include "SimplexNoise.h"
#include <vector>
#include <map>

class LuaInterface;

class World
{
private:
	int WorldGameVersionMinor;
	int WorldGameVersionMajor;
	std::string WorldGameVersionName;

	SimplexNoise randgen;

	std::string worldname;

	const uint64_t SEED;
	const static int ENTITY_UPDATE_RATE = 5; //HOW MANY TICKS BEFORE CALLING `UpdateEntityVector()`
	bool doDynamicWorldGen;

	std::map<int, std::map<int, WorldChunk*>> chunks;

	static const float entityUpdatesUntilRefresh;
	int entityUpdates;
	std::vector<Entity*> entities;

	int loadedChunkCount;

	void UpdateEntityVector();

	PlayerEntity* player;

	GroundTile* GenerateGroundTile(int x, int y);

	float GenerateGetLevelHeight(int x, int y);
	float GenerateGetLevelTemperature(int x, int y);
	float GenerateGetLevelHumidity(int x, int y);

	World(bool w, const uint64_t s, std::string name, std::string n, int min, int maj);

	Tile* GenerateTile(int x, int y);

public:
	inline WorldChunk* GetChunk(int x, int y);

	Tile* RemoveTile(int x, int y);

	void AddEntity(Entity* e);

	void Tick();

	const PlayerEntity* GetPlayer() const;

	void GenerateChunk(int x, int y);

	GroundTile* GetGroundTile(int x, int y);
	GroundTile* SetGroundTile(GroundTile* gtile, int x, int y);

	Tile* GetTile(int x, int y);
	Tile* SetTile(Tile* tile, int x, int y);

	bool IsChunkGenerated(int x, int y);

	Entity* GetEntityAtPos(float x, float y) const;
	Entity* GetEntityAtPos(float x, float y, Entity* ignore) const;

	void Draw();

	static World* LoadWorldFromFile(std::string filename);

	void SaveToFile(std::string filename);

	static World* CreateNewWorld(std::string name);

	friend WorldChunk;
	friend LuaInterface;
	friend int main();
};

