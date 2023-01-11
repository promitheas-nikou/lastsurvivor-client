#include "Quest.h"
#include "Entity.h"
#include "Tile.h"
#include "GroundTile.h"
#include "QuestCollection.h"
#include "ResourceLoader.h"

Quest::QuestCompletionRequirement::QuestCompletionRequirement(std::string id) : id{ id }
{}

bool Quest::QuestCompletionRequirement::Check() const
{
    return targetquest->IsCompleted();
}

void Quest::QuestCompletionRequirement::Resolve(QuestCollection* col)
{
    targetquest = col->GetQuest(id);
}

Quest::TileMineRequirement::TileMineRequirement(std::string tileid, int goal) : tileid{ tileid }, count{ goal }, progress{ 0 }
{}

Quest::TileMineRequirement::TileMineRequirement(std::string tileid, int progress, int goal) : tileid{ tileid }, count{ goal }, progress{ progress }
{}

void Quest::TileMineRequirement::Progress(Tile* tile)
{
    if (tile->GetID() == tileid)
        progress++;
}

bool Quest::TileMineRequirement::Check() const
{
    return progress>=count;
}

Quest::GroundTileMineRequirement::GroundTileMineRequirement(std::string gtileid, int goal) : gtileid{ gtileid }, count{ goal }, progress{ 0 }
{}

Quest::GroundTileMineRequirement::GroundTileMineRequirement(std::string gtileid, int progress, int goal) : gtileid{ gtileid }, count{ goal }, progress{ progress }
{
}

void Quest::GroundTileMineRequirement::Progress(GroundTile* gtile)
{
    if (gtile->GetID() == gtileid)
        progress++;
}

bool Quest::GroundTileMineRequirement::Check() const
{
    return progress >= count;
}

Quest::EntityKillRequirement::EntityKillRequirement(std::string entityid, int goal) : entityid{ entityid }, count{ goal }, progress{ 0 }
{}

Quest::EntityKillRequirement::EntityKillRequirement(std::string entityid, int progress, int goal) : entityid{ entityid }, count{ goal }, progress{ progress }
{}

void Quest::EntityKillRequirement::Progress(Entity* entity)
{
    if (entity->GetID() == entityid)
        progress++;
}

bool Quest::EntityKillRequirement::Check() const
{
    return progress >= count;
}

Quest::Quest(std::string id, std::string n, std::string iid, int xpos, int ypos, bool c, bool u) : id{ id }, name{ n }, iconid{ iid }, x{ xpos }, y{ ypos }, completed{ c }, unlocked{ u }
{
    icon = loaded_bitmaps[iconid];
}

bool Quest::IsCompleted() const
{
    return completed;
}

bool Quest::IsUnlocked() const
{
    return unlocked;
}

void Quest::Unlock()
{
    unlocked = true;
}

std::string Quest::GetName() const
{
    return name;
}

void Quest::Update()
{
    if (!unlocked)
    {
        for (QuestCompletionRequirement& q : quest_requirements)
            if (!q.Check())
                return;
        unlocked = true;
    }
    if (!completed)
    {
        for (TileMineRequirement& q : tile_requirements)
            if (!q.Check())
                return;
        for (GroundTileMineRequirement& q : gtile_requirements)
            if (!q.Check())
                return;
        for (EntityKillRequirement& q : kill_requirements)
            if (!q.Check())
                return;
    }
    completed = true;
}

void Quest::TileMined(Tile* tile, Tool* tool)
{
    if (unlocked)
        for (TileMineRequirement& r : tile_requirements)
            if (!r.Check())
                r.Progress(tile);
}

void Quest::GroundTileMined(GroundTile* gtile, Tool* tool)
{
    if (unlocked)
        for (GroundTileMineRequirement& r : gtile_requirements)
            if (!r.Check())
                r.Progress(gtile);
}

void Quest::EntityKilled(Entity* entity)
{
    if(unlocked)
        for (EntityKillRequirement& r : kill_requirements)
            if (!r.Check())
                r.Progress(entity);
}

int Quest::GetXpos() const
{
    return x;
}

int Quest::GetYpos() const
{
    return y;
}

int Quest::GetTileMineRequirementCount() const
{
    return tile_requirements.size();
}

void Quest::EraseTileMineRequirement(int index)
{
    tile_requirements.erase(tile_requirements.begin() + index);
}

void Quest::AddTileMineRequirement(std::string id, int count)
{
    tile_requirements.push_back(TileMineRequirement(id, count));
}

const Quest::TileMineRequirement& Quest::GetTileMineRequirement(int index) const
{
    return tile_requirements[index];
}

int Quest::GetGroundTileMineRequirementCount() const
{
    return gtile_requirements.size();
}

void Quest::EraseGroundTileMineRequirement(int index)
{
    gtile_requirements.erase(gtile_requirements.begin() + index);
}

void Quest::AddGroundTileMineRequirement(std::string id, int count)
{
    gtile_requirements.push_back(GroundTileMineRequirement(id, count));
}

const Quest::GroundTileMineRequirement& Quest::GetGroundTileMineRequirement(int index) const
{
    return gtile_requirements[index];
}

int Quest::GetEntityKillRequirementCount() const
{
    return kill_requirements.size();
}

void Quest::EraseEntityKillRequirement(int index)
{
    kill_requirements.erase(kill_requirements.begin() + index);
}

void Quest::AddEntityKillRequirement(std::string id, int count)
{
    kill_requirements.push_back(EntityKillRequirement(id, count));
}

const Quest::EntityKillRequirement& Quest::GetEntityKillRequirement(int index) const
{
    return kill_requirements[index];
}

int Quest::GetQuestCompletionRequirementCount() const
{
    return quest_requirements.size();
}

void Quest::EraseQuestCompletionRequirement(int index)
{
    quest_requirements.erase(quest_requirements.begin() + index);
}

void Quest::AddQuestCompletionRequirement(std::string id)
{
    quest_requirements.push_back(QuestCompletionRequirement(id));
}

const Quest::QuestCompletionRequirement& Quest::GetQuestCompletionRequirement(int index) const
{
    return quest_requirements[index];
}

ALLEGRO_BITMAP* Quest::GetIcon() const
{
    return icon;
}

void Quest::Resolve()
{
    for (QuestCompletionRequirement& c : quest_requirements)
        c.Resolve(collection);
}

std::string Quest::GetID() const
{
    return id;
}

std::string Quest::GetIconID() const
{
    return iconid;
}

#include <iostream>

Quest* Quest::MakeFromJSON(nlohmann::json data, QuestCollection* col)
{
    std::cout << data << std::endl;
    Quest* q = new Quest(data["id"],data["name"], data["icon"], data["xpos"], data["ypos"], data["completed"], data["unlocked"]);
    q->collection = col;

    int i = 0;

    for (nlohmann::json req : data["requirements"])
    {
        std::string t = req["type"];
        std::cout << req;
        if (t == "complete_quest")
            q->quest_requirements.push_back(QuestCompletionRequirement(req["quest"]));
        else if (t == "tile_mine")
            q->tile_requirements.push_back(TileMineRequirement(req["tile"], req.value("progress",0), req["count"]));
        else if (t == "gtile_mine")
            q->gtile_requirements.push_back(GroundTileMineRequirement(req["gtile"], req.value("progress", 0), req["count"]));
        else if (t == "kill_entity")
            q->kill_requirements.push_back(EntityKillRequirement(req["entity"], req.value("progress", 0), req["count"]));
        i++;
    }
    return q;
}

Quest* Quest::MakeNewQuest(std::string id, std::string n, std::string iid, int xpos, int ypos, bool c, bool u)
{
    return new Quest(id,n,iid,xpos, ypos,c,u);
}

void Quest::Modify(std::string n, std::string iid, int xpos, int ypos, bool c, bool u)
{
    name = n;
    iconid = iid;
    icon = loaded_bitmaps[iid];
    x = xpos;
    y = ypos;
    completed = c;
    unlocked = u;
}

nlohmann::json Quest::SerializeToJSON()
{
    nlohmann::json data;
    data["id"] = id;
    data["name"] = name;
    data["xpos"] = x;
    data["ypos"] = y;
    data["icon"] = iconid;
    data["completed"] = completed;
    data["unlocked"] = unlocked;
    nlohmann::json requirements = nlohmann::json::array();
    nlohmann::json requirement;
    for (const QuestCompletionRequirement& q : quest_requirements) {
        requirement = nlohmann::json::object();
        requirement["type"] = "complete_quest";
        requirement["quest"] = q.id;
        requirements.push_back(requirement);
    }
    for (const TileMineRequirement& q : tile_requirements) {
        requirement = nlohmann::json::object();
        requirement["type"] = "tile_mine";
        requirement["tile"] = q.tileid;
        requirement["count"] = q.count;
        requirement["progress"] = q.progress;
        requirements.push_back(requirement);
    }
    for (const GroundTileMineRequirement& q : gtile_requirements) {
        requirement = nlohmann::json::object();
        requirement["type"] = "gtile_mine";
        requirement["gtile"] = q.gtileid;
        requirement["count"] = q.count;
        requirement["progress"] = q.progress;
        requirements.push_back(requirement);
    }
    for (const EntityKillRequirement& q : kill_requirements){
        requirement = nlohmann::json::object();
        requirement["type"] = "gtile_mine";
        requirement["entity"] = q.entityid;
        requirement["count"] = q.count;
        requirement["progress"] = q.progress;
        requirements.push_back(requirement);
    }
    data["requirements"] = requirements;
    return data;
}
