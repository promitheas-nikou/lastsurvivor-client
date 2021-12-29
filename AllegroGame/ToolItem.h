#pragma once

#include "Tool.h"
#include "Item.h"

class ToolItem:
	public Tool,
	public Item
{
protected:
	ToolItem(std::string name);

};

