#include "QuestCollection.h"

QuestCollection* QuestCollection::NULL_COLLECTION;

void QuestCollection::TileMined(Tile* tile, Tool* tool)
{
	for (const std::pair<std::string, Quest*>& p : quests)
		if (p.second)
			p.second->TileMined(tile, tool);
}

void QuestCollection::MinedGroundTile(GroundTile* gtile, Tool* tool)
{
	for (const std::pair<std::string, Quest*>& p : quests)
		if (p.second)
			p.second->GroundTileMined(gtile, tool);
}

void QuestCollection::EntityKilled(Entity* entity)
{
	for (const std::pair<std::string, Quest*>& p : quests)
		if (p.second)
			p.second->EntityKilled(entity);
}

QuestCollection* QuestCollection::GetNullCollection()
{
	if (NULL_COLLECTION == nullptr)
		NULL_COLLECTION = new QuestCollection();
	return NULL_COLLECTION;
}

QuestCollection* QuestCollection::MakeNewCollection()
{
	return new QuestCollection();
}

void QuestCollection::Update()
{
	for (const std::pair<std::string, Quest*>& p : quests)
		if(p.second)
			p.second->Update();
}

void QuestCollection::Resolve()
{
	for (const std::pair<std::string, Quest*>& p : quests)
		if (p.second)
			p.second->Resolve();
}

Quest* QuestCollection::GetQuest(std::string id)
{
	return quests[id];
}

Quest* QuestCollection::GetQuest(int ind)
{
	return questsNumbered[ind];
}

void QuestCollection::ModifyQuest(std::string id, std::string name, std::string iconid, int xpos, int ypos, bool c, bool u)
{
	return GetQuest(id)->Modify(name, iconid, xpos, ypos, c, u);
}

void QuestCollection::ReIDQuest(std::string oldID, std::string newID)
{
	/*
	Quest* q = quests[oldID];
	q->id = newID;
	quests[newID] = q;
	quests[oldID] = nullptr;
	*/
}

int QuestCollection::GetQuestCount() const
{
	return questsNumbered.size();
}

void QuestCollection::AddQuest(Quest* q)
{
	q->collection = this;
	quests[q->GetID()] = q;
	questsNumbered.push_back(q);
}

#include <iostream>

QuestCollection* QuestCollection::LoadFromFile(std::istream& file)
{
	nlohmann::json data;
	QuestCollection* qc = new QuestCollection();
	try {
		data = nlohmann::json::parse(file);//std::ifstream("LastSurvivorTemp\\quests.json"));
	}
	catch (nlohmann::json::parse_error e)
	{
		std::cout << e.what() << std::endl;
	}
	for (nlohmann::json j : data["quests"])
		qc->quests[j["id"]] = Quest::MakeFromJSON(j, qc);

	for (const std::pair<std::string, Quest*>& p : qc->quests)
		if (p.second)
			qc->questsNumbered.push_back(p.second);
	qc->Resolve();
	return qc;
}

void QuestCollection::SaveToFile(std::ostream& file)
{
	nlohmann::json data = nlohmann::json::object();
	nlohmann::json questjson = nlohmann::json::array();
	for (const std::pair<std::string,Quest*> &q : quests) {
		if(q.second)
			questjson.push_back(q.second->SerializeToJSON());
	}
	data["quests"] = questjson;
	file << data;
}

