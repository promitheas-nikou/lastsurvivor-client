#include "Tool.h"

ToolType Tool::GetToolTypeFromString(std::string str)
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
