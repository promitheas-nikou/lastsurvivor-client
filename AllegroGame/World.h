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
	bool doTileTick = true;
	bool doEntityTick = true;
	int WorldGameVersionMinor;
	int WorldGameVersionMajor;
	double TPSmeasured = 50.;
	std::string WorldGameVersionName;
	static ALLEGRO_BITMAP* nullTileBitmap;
	QuestCollection* questCollection;

	SimplexNoise randgen;

	int gametime; //90000 ticks (30 minutes) is 1 day

	ALLEGRO_COLOR CalcAmbientColor();

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


	float GenerateGetLevelHeight(int x, int y);
	float GenerateGetLevelTemperature(int x, int y);
	float GenerateGetLevelHumidity(int x, int y);
	float GenerateGetLevelOreQualityFactor(int x, int y);
	float GenerateGetLevelOreDensityFactor(int x, int y);
	float GenerateGetLevelTileRandomness(int x, int y);

	World(bool w, const uint64_t s, std::string name, std::string n, int min, int maj);

	Tile* GenerateTile(int x, int y);
	GroundTile* GenerateGroundTile(int x, int y);

public:

	double GetMeasuredTPS();

	inline WorldChunk* GetChunk(int x, int y);

	Tile* RemoveTile(int x, int y);

	void AddEntity(Entity* e);

	void Tick();

	PlayerEntity* GetPlayer() const;

	void GenerateChunk(int x, int y);

	GroundTile* GetGroundTile(int x, int y);
	GroundTile* SetGroundTile(GroundTile* gtile, int x, int y);

	Tile* GetTile(int x, int y);
	Tile* SetTile(Tile* tile, int x, int y);

	bool IsChunkGenerated(int x, int y);

	void TileUpdateAround(int x, int y);

	Entity* GetEntityAtPos(float x, float y, Entity* ignore = nullptr) const;
	Entity* GetEntityColliding(Entity* entity, Entity* ignore = nullptr) const;

	std::vector<Entity*> GetEntitiesAtPos(float x, float y) const;
	std::vector<Entity*> GetEntitiesColliding(Entity* e) const;

	QuestCollection* GetQuestCollection() const;

	class Light {
	private:
		float xpos;
		float ypos;
		float brightness;
	public:
		Light(float x, float y, float b);
		float GetXpos() const;
		float GetYpos() const;
		float GetBrightness() const;
		~Light() = default;
	};

	void RegisterLight(Light l);

	void Draw();

	static World* LoadWorldFromFile(std::string filename);

	void SaveToFile(std::string filename);

	static void Init();

	static World* CreateNewWorld(std::string name, uint64_t seed, std::function<void(int curx, int cury, int p, int t)>);
	static World* CreateNewFixedSizeWorld(std::string name, uint64_t seed, int minChunkX, int minChunkY, int maxChunkX, int maxChunkYvoid, std::function<void(int curx, int cury, int p, int t)>);

	friend WorldChunk;
	friend LuaInterface;
	friend PlayerEntity;
	friend int main();
};

