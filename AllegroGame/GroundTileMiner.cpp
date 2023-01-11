#include "GroundTileMiner.h"
#include "World.h"

int GroundTileMiner::GetMiningDamageDone() const
{
    return miningDamageDone;
}

void GroundTileMiner::SetTool(Tool* newTool)
{
    tool = newTool;
}

Tool* GroundTileMiner::GetTool() const
{
    return tool;
}

ItemInventory* GroundTileMiner::GetTargetItemInventory() const
{
    return inventory;
}

void GroundTileMiner::SetTargetItemInventory(ItemInventory* inv)
{
    inventory = inv;
}

void GroundTileMiner::SetTarget(World* w, int x, int y)
{
    if (gtileX == x && gtileY == y)
        return;
    world = w;
    gtileX = x;
    gtileY = y;
    miningDamageDone = 0;
}

GroundTile* GroundTileMiner::GetTarget() const
{
    return world->GetGroundTile(gtileX,gtileY);
}

void GroundTileMiner::AddResult(const ItemBundle* b)
{
    inventory->AddConstItemBundle(b);
}

void GroundTileMiner::ResetProgress()
{
    miningDamageDone = 0;
}

bool GroundTileMiner::Mine()
{
    GroundTile* target = world->GetGroundTile(gtileX, gtileY);
    if (target == nullptr)
        return false;
    miningDamageDone += target->GetDamageDealtByTool(tool);
    int tmp = target->GetMiningResistance();
    if (miningDamageDone >= tmp)
    {
        for (int i = 0; i < miningDamageDone / tmp; i++)
            this->AddResult(target->GetMiningResult(tool));
        miningDamageDone %= tmp;
        return true;
    }
    else
        return false;
    
}

GroundTileMiner::GroundTileMiner(Tool* t, ItemInventory* inv, World* w, int x, int y) : tool{ t }, inventory{ inv }, miningDamageDone{ 0 }, world{ w }, gtileX{ x }, gtileY{ y }
{}
