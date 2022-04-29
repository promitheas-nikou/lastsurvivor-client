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

void Quest::EntityKillRequirement::Progress(Entity* entity)
{
    if (entity->GetID() == entityid)
        progress++;
}

bool Quest::EntityKillRequirement::Check() const
{
    return progress >= count;
}

Quest::Quest(std::string id, std::string n, ALLEGRO_BITMAP* b, bool c, bool u) : id{ id }, name{ n }, icon{ b }, completed{ c }, unlocked{ u }
{}

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

#include <iostream>

Quest* Quest::MakeFromJSON(nlohmann::json data, QuestCollection* col)
{
    Quest* q = new Quest(data["id"],data["name"], loaded_bitmaps[data["icon"]],data["completed"], data["unlocked"]);
    q->collection = col;
    q->x = data["xpos"];
    q->y = data["ypos"];
    for (nlohmann::json req : data["requirements"])
    {
        std::string t = req["type"];
        std::cout << req;
        if (t == "complete_quest")
            q->quest_requirements.push_back(QuestCompletionRequirement(req["quest"]));
        else if (t == "tile_mine")
            q->tile_requirements.push_back(TileMineRequirement(req["tile"], req["count"]));
        else if (t == "gtile_mine")
            q->gtile_requirements.push_back(GroundTileMineRequirement(req["gtile"], req["count"]));
        else if (t == "kill_entity")
            q->kill_requirements.push_back(EntityKillRequirement(req["entity"], req["count"]));
    }
    printf("LOADED QUEST \"%s\"\n", q->GetID().c_str());
    return q;
}
