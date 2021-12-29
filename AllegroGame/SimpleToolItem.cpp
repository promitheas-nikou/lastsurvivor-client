#include "SimpleToolItem.h"

SimpleToolItem::SimpleToolItem(std::string name, int miningDmg, ToolType type) : ToolItem(name), miningDamage{ miningDmg }, toolType{ type }
{}

ToolType SimpleToolItem::GetMiningType() const
{
    return toolType;
}

int SimpleToolItem::GetMiningDamage() const
{
    return miningDamage;
}
