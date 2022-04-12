#include "InventoryGUI.h"
#include "ResourceLoader.h"


ALLEGRO_BITMAP* INVENTORY_SLOT;
ALLEGRO_BITMAP* INVENTORY_SLOT_CONSUME;

SlotDisplayConfiguration::SlotDisplayConfiguration(int s, int x, int y) : SlotDisplayConfiguration(s, x, y, 128, 128)
{}

SlotDisplayConfiguration::SlotDisplayConfiguration(int s, int x, int y, int w, int h) : type{ SLOT_DISPLAY_CONFIGURATION_TYPE::STORAGE }, itemID { s }, xpos{ x }, ypos{ y }, width{ w }, height{ h }, callback{ nullptr }
{}

SlotDisplayConfiguration::SlotDisplayConfiguration(bool(*c)(Item*), int x, int y) : SlotDisplayConfiguration(c, x, y, 128, 128)
{}

SlotDisplayConfiguration::SlotDisplayConfiguration(bool(*c)(Item*), int x, int y, int w, int h) : type{ SLOT_DISPLAY_CONFIGURATION_TYPE::FUNCTION }, itemID{ -1 }, xpos{ x }, ypos{ y }, width{ w }, height{ h }, callback{ c }
{}

bool SlotDisplayConfiguration::contains(int x, int y) const
{
	return (x>=xpos)&&(y>=ypos)&&(x<=xpos+width)&&(y<=ypos+height);
}

SLOT_DISPLAY_CONFIGURATION_TYPE SlotDisplayConfiguration::getType() const
{
	return type;
}

bool SlotDisplayConfiguration::execute(Item* item) const
{
	return callback(item);
}

void InventoryGUI::SwapItem(int slotID)
{
	Item* tmp = GetItem(slotID);
	SetItem(slotID, swapTemp);
	swapTemp = tmp;
}

void InventoryGUI::ClickLeftDown(int x, int y)
{
	for (const SlotDisplayConfiguration& slot : slots)
	{
		if (slot.contains(x, y))
		{
			switch (slot.getType())
			{
			case SLOT_DISPLAY_CONFIGURATION_TYPE::STORAGE:
				SwapItem(slot.itemID);
				return;
			case SLOT_DISPLAY_CONFIGURATION_TYPE::FUNCTION:
				if (slot.execute(swapTemp))
					swapTemp = nullptr;
				return;
			}
			return;
		}
	}
}

InventoryGUI::InventoryGUI()
{
	INVENTORY_SLOT = loaded_bitmaps["tex.gui.inventory_slot"];
	INVENTORY_SLOT_CONSUME = loaded_bitmaps["tex.gui.inventory_slot_consume"];
}

void InventoryGUI::DrawSlot(const SlotDisplayConfiguration& data)
{
	switch (data.getType())
	{
	case SLOT_DISPLAY_CONFIGURATION_TYPE::FUNCTION:
		al_draw_scaled_bitmap(INVENTORY_SLOT_CONSUME, 0, 0, al_get_bitmap_width(INVENTORY_SLOT_CONSUME), al_get_bitmap_height(INVENTORY_SLOT_CONSUME), data.xpos - 2, data.ypos - 2, data.width + 4, data.height + 4, 0);
		break;
	case SLOT_DISPLAY_CONFIGURATION_TYPE::STORAGE:
		al_draw_scaled_bitmap(INVENTORY_SLOT, 0, 0, al_get_bitmap_width(INVENTORY_SLOT), al_get_bitmap_height(INVENTORY_SLOT), data.xpos - 2, data.ypos - 2, data.width + 4, data.height + 4, 0);
		Item* i = this->GetItem(data.itemID);
		if (i != nullptr)
			i->Draw(data.xpos, data.ypos, data.width, data.height);
		break;
	}
}

void InventoryGUI::DrawThisGUI()
{
	for (const SlotDisplayConfiguration& slot : slots)
		DrawSlot(slot);
	int x, y;
	al_get_mouse_cursor_position(&x,&y);
	if(swapTemp!=nullptr)
		swapTemp->Draw(x-64, y-64, 128, 128);
}

void InventoryGUI::AddSlotDisplayConfiguration(SlotDisplayConfiguration slot)
{
	slots.push_back(slot);
}
