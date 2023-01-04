#pragma once
#include "Tool.h"
class SimpleTool :
    public virtual Tool
{
private:
    ToolType type;
    int damage;
    
protected:

    void SetToolType(ToolType newtype);
    void SetDamage(float dmg);

public:

    SimpleTool(ToolType t, int d);

    virtual ToolType GetToolType() const final;
    virtual float GetMiningDamage() const final;

    virtual ~SimpleTool() = default;

};

