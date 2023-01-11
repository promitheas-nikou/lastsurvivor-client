#include "SimpleTool.h"

void SimpleTool::SetToolType(ToolType newtype)
{
    type = newtype;
}

void SimpleTool::SetDamage(float dmg)
{
    damage = dmg;
}

SimpleTool::SimpleTool(ToolType t, int d) : type{ t }, damage{ d }
{}

Tool::ToolType SimpleTool::GetToolType() const
{
    return type;
}

float SimpleTool::GetMiningDamage() const
{
    return damage;
}
