#pragma once

#include "Tool.h"
#include "Item.h"

class ToolItem:
	public virtual Tool,
	public virtual Item
{
protected:
	ToolItem(std::string name);
	virtual ~ToolItem() = default;
};

