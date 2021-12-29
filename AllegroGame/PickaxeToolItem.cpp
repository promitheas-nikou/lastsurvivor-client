#include "PickaxeToolItem.h"

PickaxeToolItem::PickaxeToolItem(std::string name, int miningDmg) : ToolItem(name), miningDamage{ miningDmg }
{}

ToolType PickaxeToolItem::GetMiningType() const
{
    return ToolType::PICKAXE;
}

int PickaxeToolItem::GetMiningDamage() const
{
    return miningDamage;
}
