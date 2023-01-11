#include "SimpleToolItem.h"

SimpleToolItem::SimpleToolItem(std::string name, int miningDmg, ToolType type) : Item(name), SimpleTool(type,miningDmg)
{}
