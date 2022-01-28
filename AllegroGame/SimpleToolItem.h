#pragma once
#include "ToolItem.h"
class SimpleToolItem :
    public ToolItem
{
protected:
    int miningDamage;
    ToolType toolType;

    SimpleToolItem(std::string name, int miningDmg, ToolType type);

public:
    virtual ToolType GetMiningType() const override;
    virtual int GetMiningDamage() const override;

    virtual ~SimpleToolItem() = default;
};

