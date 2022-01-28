#pragma once

#include <string>

enum class ToolType : char {
	NONE = 0b0000,
	PICKAXE = 0b0001,
	AXE = 0b0010,
	SHOVEL = 0b0100,
	PUMP = 0b1000
};

class Tool
{
public:
	virtual ToolType GetMiningType() const = 0;
	virtual int GetMiningDamage() const = 0;

	static ToolType GetToolTypeFromString(std::string str);

	virtual ~Tool() = default;
};

