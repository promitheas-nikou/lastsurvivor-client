#include "InventoryGUI.h"
#include "ResourceLoader.h"

SlotDisplayConfiguration::SlotDisplayConfiguration(int s, int x, int y) : SlotDisplayConfiguration(s, x, y, 128, 128)
{}

SlotDisplayConfiguration::SlotDisplayConfiguration(int s, int x, int y, int w, int h): itemID { s }, xpos{ x }, ypos{ y }, width{ w }, height{ h }
{}

bool SlotDisplayConfiguration::contains(int x, int y) const
{
	return (x>=xpos)&&(y>=ypos)&&(x<=xpos+width)&&(y<=ypos+height);
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
			SwapItem(slot.itemID);
			return;
		}
	}
}

void InventoryGUI::DrawSlot(const SlotDisplayConfiguration& data)
{
	ALLEGRO_BITMAP* bmp = loaded_bitmaps["tex.gui.hotbar_slot"];
	al_draw_scaled_bitmap(bmp, 0, 0, al_get_bitmap_width(bmp), al_get_bitmap_height(bmp), data.xpos - 2, data.ypos - 2, data.width + 4, data.height + 4, 0);
	Item* i = this->GetItem(data.itemID);
	if (i != nullptr)
		i->Draw(data.xpos, data.ypos, data.width, data.height);
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
