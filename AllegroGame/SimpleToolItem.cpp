#include "SimpleToolItem.h"

SimpleToolItem::SimpleToolItem(std::string name, int miningDmg, ToolType type) : ToolItem(name), SimpleTool(type,miningDmg)
{}
