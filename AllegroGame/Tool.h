#pragma once

enum class ToolType {NONE, PICKAXE, AXE, SHOVEL, PUMP};

class Tool
{
public:
	virtual ToolType GetMiningType() const = 0;
	virtual int GetMiningDamage() const = 0;
};

