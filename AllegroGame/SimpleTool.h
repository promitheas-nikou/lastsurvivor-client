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
    void SetDamage(int dmg);

public:

    SimpleTool(ToolType t, int d);

    virtual ToolType GetMiningType() const final;
    virtual int GetMiningDamage() const final;

    virtual ~SimpleTool() = default;

};

