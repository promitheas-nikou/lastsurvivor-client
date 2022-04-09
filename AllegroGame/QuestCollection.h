#pragma once
#include <unordered_map>
#include <string>
#include "Quest.h"

class QuestCollection
{
private:
	std::unordered_map<std::string, Quest*> quests;
	QuestCollection() = default;
public:
	void TileMined(Tile* tile, Tool* tool);
	void MinedGroundTile(GroundTile* gtile, Tool* tool);
	void EntityKilled(Entity* entity);

	static QuestCollection* MakeFromJSON(nlohmann::json data);
	friend Quest;
};

