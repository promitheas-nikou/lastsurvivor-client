#pragma once
#include <string>
#include <vector>
#include "json.h"

class QuestCollection;
class Tile;
class GroundTile;
class Tool;
class Entity;

class Quest
{
private:
	std::string name;
	std::string id;
	bool completed;
	bool unlocked;
	QuestCollection* collection;

	class QuestCompletionRequirement {
	public:
		Quest* targetquest;
		QuestCompletionRequirement(Quest* quest);
		bool Check() const;
	};

	class TileMineRequirement {
	public:
		std::string tileid;
		int count;
		int progress;
		bool completed = false;
		TileMineRequirement(std::string tileid, int goal);
		void Progress(Tile* tile);
		bool Check() const;
	};

	class GroundTileMineRequirement {
	public:
		std::string gtileid;
		int count;
		int progress;
		bool completed = false;
		GroundTileMineRequirement(std::string gtileid, int goal);
		void Progress(GroundTile* gtile);
		bool Check() const;
	};

	class EntityKillRequirement {
	public:
		std::string entityid;
		int count;
		int progress;
		bool completed = false;
		EntityKillRequirement(std::string entityid, int goal);
		void Progress(Entity* entity);
		bool Check() const;	
	};

	std::vector<QuestCompletionRequirement> quest_requirements;
	std::vector<TileMineRequirement> tile_requirements;
	std::vector<GroundTileMineRequirement> gtile_requirements;
	std::vector<EntityKillRequirement> kill_requirements;

	Quest(std::string id, std::string n, bool c, bool u);
public:
	bool IsCompleted() const;
	bool IsUnlocked() const;
	
	void Unlock();

	void TileMined(Tile* tile, Tool* tool);
	void GroundTileMined(GroundTile* gtile, Tool* tool);
	void EntityKilled(Entity* entity);

	std::string GetID() const;

	static Quest *MakeFromJSON(nlohmann::json data, QuestCollection* col);
	friend QuestCollection;
};

