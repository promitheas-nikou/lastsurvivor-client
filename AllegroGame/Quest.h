#pragma once
#include <string>
#include <vector>
#include "json.h"
#include <fstream>
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
	std::string iconid;
	ALLEGRO_BITMAP* icon;
	bool completed;
	bool unlocked;
	int x;
	int y;
	QuestCollection* collection;
public:
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
		TileMineRequirement(std::string tileid, int progress, int goal);
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
		GroundTileMineRequirement(std::string gtileid, int progress, int goal);
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
		EntityKillRequirement(std::string entityid, int progress, int goal);
		void Progress(Entity* entity);
		bool Check() const;	
	};
private:
	std::vector<QuestCompletionRequirement> quest_requirements;
	std::vector<TileMineRequirement> tile_requirements;
	std::vector<GroundTileMineRequirement> gtile_requirements;
	std::vector<EntityKillRequirement> kill_requirements;

	Quest(std::string id, std::string n, std::string iid, int xpos, int ypos, bool c, bool u);
public:
	bool IsCompleted() const;
	bool IsUnlocked() const;
	
	void Unlock();

	std::string GetName() const;

	void Update();

	void TileMined(Tile* tile, Tool* tool);
	void GroundTileMined(GroundTile* gtile, Tool* tool);
	void EntityKilled(Entity* entity);

	int GetXpos() const;
	int GetYpos() const;

	int GetTileMineRequirementCount() const;
	void EraseTileMineRequirement(int index);
	void AddTileMineRequirement(std::string id, int count);
	const TileMineRequirement& GetTileMineRequirement(int index) const;

	int GetGroundTileMineRequirementCount() const;
	void EraseGroundTileMineRequirement(int index);
	void AddGroundTileMineRequirement(std::string id, int count);
	const GroundTileMineRequirement& GetGroundTileMineRequirement(int index) const;

	int GetEntityKillRequirementCount() const;
	void EraseEntityKillRequirement(int index);
	void AddEntityKillRequirement(std::string id, int count);
	const EntityKillRequirement& GetEntityKillRequirement(int index) const;

	int GetQuestCompletionRequirementCount() const;
	void EraseQuestCompletionRequirement(int index);
	void AddQuestCompletionRequirement(std::string id);
	const QuestCompletionRequirement& GetQuestCompletionRequirement(int index) const;

	ALLEGRO_BITMAP* GetIcon() const;

	void Resolve();

	std::string GetID() const;
	std::string GetIconID() const;

	static Quest *MakeFromJSON(nlohmann::json data, QuestCollection* col);
	static Quest *MakeNewQuest(std::string id, std::string n, std::string iid, int xpos, int ypos, bool c, bool u);
	void Modify(std::string n, std::string iid, int xpos, int ypos, bool c, bool u);
	nlohmann::json SerializeToJSON();
	friend QuestCollection;
	friend class QuestGUI;
};

