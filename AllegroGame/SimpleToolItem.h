#pragma once
#include "SimpleTool.h"
#include "ToolItem.h"

class SimpleToolItem :
    public virtual SimpleTool,
    public virtual ToolItem
{
public:
     
    SimpleToolItem(std::string name, int miningDmg, ToolType type);

    virtual ~SimpleToolItem() = default;
};

