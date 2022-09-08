#include "QuestCollection.h"

QuestCollection* QuestCollection::NULL_COLLECTION;

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

QuestCollection* QuestCollection::GetNullCollection()
{
    if (NULL_COLLECTION == nullptr)
        NULL_COLLECTION = new QuestCollection();
    return NULL_COLLECTION;
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

#include <iostream>

QuestCollection* QuestCollection::LoadFromFile(std::ifstream& file)
{
    nlohmann::json data;
    QuestCollection* qc = new QuestCollection();
    try {
        data = nlohmann::json::parse(file);//std::ifstream("C:\\Users\\promitheas\\AppData\\Local\\Temp\\LastSurvivorTemp\\quests.json"));
    }
    catch (nlohmann::json::parse_error e)
    {
        std::cout << e.what() << std::endl;
    }
    for (nlohmann::json j : data["quests"])
        qc->quests[j["id"]] = Quest::MakeFromJSON(j, qc);
    return qc;
}

void QuestCollection::SaveToFile(std::ofstream& file)
{
    nlohmann::json data = nlohmann::json::object();
    nlohmann::json questjson = nlohmann::json::array();
    for (const std::pair<std::string,Quest*> &q : quests) {
        questjson.push_back(q.second->SerializeToJSON());
    }
    data["quests"] = questjson;
    file << data;
}

