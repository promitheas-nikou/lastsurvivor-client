#pragma once
#include <string>
#include <vector>
#include "json.h"
#include <allegro5/allegro5.h>

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
	ALLEGRO_BITMAP* icon;
	bool completed;
	bool unlocked;
	int x;
	int y;
	QuestCollection* collection;

	class QuestCompletionRequirement {
	public:
		std::string id;
		Quest* targetquest;
		QuestCompletionRequirement(std::string id);
		bool Check() const;
		void Resolve(QuestCollection* col);
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

	Quest(std::string id, std::string n, ALLEGRO_BITMAP* b, bool c, bool u);
public:
	bool IsCompleted() const;
	bool IsUnlocked() const;
	
	void Unlock();

	std::string GetName() const;

	void Update();

	void TileMined(Tile* tile, Tool* tool);
	void GroundTileMined(GroundTile* gtile, Tool* tool);
	void EntityKilled(Entity* entity);

	ALLEGRO_BITMAP* GetIcon() const;

	void Resolve();

	std::string GetID() const;

	static Quest *MakeFromJSON(nlohmann::json data, QuestCollection* col);
	friend QuestCollection;
	friend class QuestGUI;
};

