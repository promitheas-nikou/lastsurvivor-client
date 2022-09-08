#pragma once
#include <unordered_map>
#include <string>
#include "Quest.h"

class QuestCollection
{
private:
	static QuestCollection* NULL_COLLECTION;
	std::unordered_map<std::string, Quest*> quests;
	QuestCollection() = default;
public:
	void TileMined(Tile* tile, Tool* tool);
	void MinedGroundTile(GroundTile* gtile, Tool* tool);
	void EntityKilled(Entity* entity);

	static QuestCollection* GetNullCollection();

	void Update();

	Quest* GetQuest(std::string id);

	static QuestCollection* LoadFromFile(std::ifstream &file);
	void SaveToFile(std::ofstream &file);
	friend Quest;
	friend class QuestGUI;
};

