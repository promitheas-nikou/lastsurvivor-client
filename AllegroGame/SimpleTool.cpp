#include "SimpleTool.h"

void SimpleTool::SetToolType(ToolType newtype)
{
    type = newtype;
}

void SimpleTool::SetDamage(int dmg)
{
    damage = dmg;
}

SimpleTool::SimpleTool(ToolType t, int d) : type{ t }, damage{ d }
{}

ToolType SimpleTool::GetMiningType() const
{
    return type;
}

int SimpleTool::GetMiningDamage() const
{
    return damage;
}
