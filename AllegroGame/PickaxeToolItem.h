#pragma once

#include "ToolItem.h"

class PickaxeToolItem :
    public ToolItem
{
protected:

    int miningDamage;

    PickaxeToolItem(std::string name, int miningDmg);

public:


    virtual ToolType GetMiningType() const final;
    virtual int GetMiningDamage() const override;

    virtual ~PickaxeToolItem() = default;
};

