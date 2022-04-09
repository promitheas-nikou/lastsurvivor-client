#include "GroundTileMiner.h"

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

void GroundTileMiner::SetTarget(GroundTile* newTarget)
{
    if (target != newTarget)
    {
        target = newTarget;
        ResetProgress();
    }
}

GroundTile* GroundTileMiner::GetTarget() const
{
    return target;
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

GroundTileMiner::GroundTileMiner(Tool* t, ItemInventory* inv) : tool{ t }, inventory{ inv }, miningDamageDone{ 0 }, target{ nullptr }
{}
