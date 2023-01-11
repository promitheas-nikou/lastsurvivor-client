#pragma once

#include "Tool.h"
#include "Item.h"

class ToolItem:
	public virtual Tool,
	public virtual Item
{
protected:

	ToolItem() = default;

	virtual int GetMaxStackSize() const override;

	virtual void DrawItemDetailsPane(int x, int y);

	virtual ~ToolItem() = 0;
};

