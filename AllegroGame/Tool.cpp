#include "Tool.h"

Tool::ToolType Tool::GetToolTypeFromString(std::string str)
{
	if (str == "pickaxe")
		return ToolType::PICKAXE;
	if (str == "axe")
		return ToolType::AXE;
	if (str == "shovel")
		return ToolType::SHOVEL;
	if (str == "none")
		return ToolType::NONE;
	return ToolType::NONE;
}

bool Tool::IsShovel() const
{
	return GetToolType() & ToolType::SHOVEL;
}

bool Tool::IsPickaxe() const
{
	return GetToolType() & ToolType::PICKAXE;
}

bool Tool::IsAxe() const
{
	return GetToolType() & ToolType::AXE;
}

bool Tool::IsPump() const
{
	return GetToolType() & ToolType::PUMP;
}

Tool::ToolType::ToolType(char v) : val{ v }
{}

Tool::ToolType::operator ToolType_t() const
{
	return val;
}
