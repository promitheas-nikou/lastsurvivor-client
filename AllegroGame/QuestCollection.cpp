#include "QuestCollection.h"

void QuestCollection::TileMined(Tile* tile, Tool* tool)
{
    for (const std::pair<std::string, Quest*>& p : quests)
        p.second->TileMined(tile, tool);
}

void QuestCollection::MinedGroundTile(GroundTile* gtile, Tool* tool)
{
    for (const std::pair<std::string, Quest*>& p : quests)
        p.second->GroundTileMined(gtile, tool);
}

void QuestCollection::EntityKilled(Entity* entity)
{
    for (const std::pair<std::string, Quest*>& p : quests)
        p.second->EntityKilled(entity);
}

void QuestCollection::Update()
{
    for (const std::pair<std::string, Quest*>& p : quests)
        p.second->Update();
}

Quest* QuestCollection::GetQuest(std::string id)
{
    return quests[id];
}

QuestCollection* QuestCollection::MakeFromJSON(nlohmann::json data)
{
    QuestCollection* qc = new QuestCollection();
    for (nlohmann::json j : data)
        qc->quests[j["id"]] = Quest::MakeFromJSON(j, qc);
    return qc;
}
