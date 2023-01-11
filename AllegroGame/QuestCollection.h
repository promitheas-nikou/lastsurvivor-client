#pragma once
#include <unordered_map>
#include <string>
#include "Quest.h"

class QuestCollection
{
private:
	static QuestCollection* NULL_COLLECTION;
	std::unordered_map<std::string, Quest*> quests;
	std::vector<Quest*> questsNumbered;
	QuestCollection() = default;
public:
	void TileMined(Tile* tile, Tool* tool);
	void MinedGroundTile(GroundTile* gtile, Tool* tool);
	void EntityKilled(Entity* entity);

	static QuestCollection* GetNullCollection();

	static QuestCollection* MakeNewCollection();

	void Update();

	void Resolve();

	Quest* GetQuest(std::string id);
	Quest* GetQuest(int ind);
	void ModifyQuest(std::string id, std::string name, std::string iconid, int xpos, int ypos, bool c, bool u);
	void ReIDQuest(std::string oldID, std::string newID);
	int GetQuestCount() const;

	void AddQuest(Quest* q);

	static QuestCollection* LoadFromFile(std::ifstream &file);
	void SaveToFile(std::ofstream &file);
	friend Quest;
	friend class QuestGUI;
};

