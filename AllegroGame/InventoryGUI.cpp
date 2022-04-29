#include "InventoryGUI.h"
#include "ResourceLoader.h"


ALLEGRO_BITMAP* InventoryGUI::INVENTORY_SLOT;
ALLEGRO_BITMAP* InventoryGUI::INVENTORY_SLOT_CALLBACK;
ALLEGRO_BITMAP* InventoryGUI::INVENTORY_SLOT_SHOVEL;
ALLEGRO_BITMAP* InventoryGUI::INVENTORY_SLOT_PICKAXE;
ALLEGRO_BITMAP* InventoryGUI::INVENTORY_SLOT_AXE;
ALLEGRO_BITMAP* InventoryGUI::INVENTORY_SLOT_MELEE;
ALLEGRO_BITMAP* InventoryGUI::INVENTORY_SLOT_RANGED;
ALLEGRO_BITMAP* InventoryGUI::INVENTORY_SLOT_CONSUMABLE;
ALLEGRO_BITMAP* InventoryGUI::INVENTORY_SLOT_PLACEABLE;

SlotDisplayConfiguration::SlotDisplayConfiguration(Item** s, int x, int y, SLOT_DISPLAY_CONFIGURATION_TYPE type) : SlotDisplayConfiguration(s, x, y, 128, 128, type)
{}

SlotDisplayConfiguration::SlotDisplayConfiguration(Item** s, int x, int y, int w, int h, SLOT_DISPLAY_CONFIGURATION_TYPE type) : type{ type }, item_slot{ s }, xpos{ x }, ypos{ y }, width{ w }, height{ h }, callback()
{}

SlotDisplayConfiguration::SlotDisplayConfiguration(std::function<Item* (Item*)> callback, int x, int y) : SlotDisplayConfiguration(callback, x, y, 128, 128)
{}

SlotDisplayConfiguration::SlotDisplayConfiguration(std::function<Item* (Item*)> callback, int x, int y, int w, int h) : type{ SLOT_DISPLAY_CONFIGURATION_TYPE::FUNCTION }, item_slot{ nullptr }, xpos{ x }, ypos{ y }, width{ w }, height{ h }, callback{ callback }
{}

bool SlotDisplayConfiguration::contains(int x, int y) const
{
	return (x>=xpos)&&(y>=ypos)&&(x<=xpos+width)&&(y<=ypos+height);
}	

SLOT_DISPLAY_CONFIGURATION_TYPE SlotDisplayConfiguration::getType() const
{
	return type;
}

Item* SlotDisplayConfiguration::execute(Item* item) const
{
	return callback(item);
}

void InventoryGUI::SwapItem(Item** slot)
{
	Item* tmp = *slot;
	if (((swapTemp != nullptr) && (tmp != nullptr)) && (swapTemp->GetID() == tmp->GetID()))
	{
		swapTemp->SetAmount(tmp->AddAmount(swapTemp->GetAmount()));
		if (swapTemp->GetAmount() <= 0)
		{
			delete swapTemp;
			swapTemp = nullptr;
		}
		return;
	}
	(*slot) = swapTemp;
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
				SwapItem(slot.item_slot);
				return;
			case SLOT_DISPLAY_CONFIGURATION_TYPE::FUNCTION:
				swapTemp = slot.execute(swapTemp);
				return;
			}
			return;
		}
	}
}

InventoryGUI::InventoryGUI() : swapTemp{ nullptr }
{
}

void InventoryGUI::Init()
{
	INVENTORY_SLOT = loaded_bitmaps["tex.gui.inventory_slot"];
	INVENTORY_SLOT_CALLBACK = loaded_bitmaps["tex.gui.inventory_slot_function"];
	INVENTORY_SLOT_SHOVEL = loaded_bitmaps["tex.gui.inventory_slot_shovel"];
	INVENTORY_SLOT_PICKAXE = loaded_bitmaps["tex.gui.inventory_slot_pickaxe"];
	INVENTORY_SLOT_AXE = loaded_bitmaps["tex.gui.inventory_slot_axe"];
	INVENTORY_SLOT_MELEE = loaded_bitmaps["tex.gui.inventory_slot_melee"];
	INVENTORY_SLOT_RANGED = loaded_bitmaps["tex.gui.inventory_slot_ranged"];
	INVENTORY_SLOT_CONSUMABLE = loaded_bitmaps["tex.gui.inventory_slot_consumable"];
	INVENTORY_SLOT_PLACEABLE = loaded_bitmaps["tex.gui.inventory_slot_placeable"];
}

void InventoryGUI::DrawSlot(const SlotDisplayConfiguration& data, bool selected)
{
	switch (data.getType())
	{
	case SLOT_DISPLAY_CONFIGURATION_TYPE::FUNCTION:
	{
		al_draw_scaled_bitmap(INVENTORY_SLOT_CALLBACK, 0, 0, al_get_bitmap_width(INVENTORY_SLOT_CALLBACK), al_get_bitmap_height(INVENTORY_SLOT_CALLBACK), data.xpos - 2, data.ypos - 2, data.width + 4, data.height + 4, 0);
		break;
	}
	case SLOT_DISPLAY_CONFIGURATION_TYPE::STORAGE:
	{
		al_draw_scaled_bitmap(INVENTORY_SLOT, 0, 0, al_get_bitmap_width(INVENTORY_SLOT), al_get_bitmap_height(INVENTORY_SLOT), data.xpos - 2, data.ypos - 2, data.width + 4, data.height + 4, 0);
		Item* i = *data.item_slot;
		if (i != nullptr)
			i->Draw(data.xpos, data.ypos, data.width, data.height);
		break;
	}
	case SLOT_DISPLAY_CONFIGURATION_TYPE::PICKAXE:
	{
		al_draw_scaled_bitmap(INVENTORY_SLOT_PICKAXE, 0, 0, al_get_bitmap_width(INVENTORY_SLOT_PICKAXE), al_get_bitmap_height(INVENTORY_SLOT_PICKAXE), data.xpos - 2, data.ypos - 2, data.width + 4, data.height + 4, 0);
		Item* i = *data.item_slot;
		if (i != nullptr)
			i->Draw(data.xpos, data.ypos, data.width, data.height);
		break;
	}
	case SLOT_DISPLAY_CONFIGURATION_TYPE::AXE:
	{
		al_draw_scaled_bitmap(INVENTORY_SLOT_AXE, 0, 0, al_get_bitmap_width(INVENTORY_SLOT_AXE), al_get_bitmap_height(INVENTORY_SLOT_AXE), data.xpos - 2, data.ypos - 2, data.width + 4, data.height + 4, 0);
		Item* i = *data.item_slot;
		if (i != nullptr)
			i->Draw(data.xpos, data.ypos, data.width, data.height);
		break;
	}
	case SLOT_DISPLAY_CONFIGURATION_TYPE::SHOVEL:
	{
		al_draw_scaled_bitmap(INVENTORY_SLOT_SHOVEL, 0, 0, al_get_bitmap_width(INVENTORY_SLOT_SHOVEL), al_get_bitmap_height(INVENTORY_SLOT_SHOVEL), data.xpos - 2, data.ypos - 2, data.width + 4, data.height + 4, 0);
		Item* i = *data.item_slot;
		if (i != nullptr)
			i->Draw(data.xpos, data.ypos, data.width, data.height);
		break;
	}
	case SLOT_DISPLAY_CONFIGURATION_TYPE::MELEE:
	{
		al_draw_scaled_bitmap(INVENTORY_SLOT_MELEE, 0, 0, al_get_bitmap_width(INVENTORY_SLOT_MELEE), al_get_bitmap_height(INVENTORY_SLOT_MELEE), data.xpos - 2, data.ypos - 2, data.width + 4, data.height + 4, 0);
		Item* i = *data.item_slot;
		if (i != nullptr)
			i->Draw(data.xpos, data.ypos, data.width, data.height);
		break;
	}
	case SLOT_DISPLAY_CONFIGURATION_TYPE::RANGED:
	{
		al_draw_scaled_bitmap(INVENTORY_SLOT_RANGED, 0, 0, al_get_bitmap_width(INVENTORY_SLOT_RANGED), al_get_bitmap_height(INVENTORY_SLOT_RANGED), data.xpos - 2, data.ypos - 2, data.width + 4, data.height + 4, 0);
		Item* i = *data.item_slot;
		if (i != nullptr)
			i->Draw(data.xpos, data.ypos, data.width, data.height);
		break;
	}
	case SLOT_DISPLAY_CONFIGURATION_TYPE::CONSUMABLE:
	{
		al_draw_scaled_bitmap(INVENTORY_SLOT_CONSUMABLE, 0, 0, al_get_bitmap_width(INVENTORY_SLOT_CONSUMABLE), al_get_bitmap_height(INVENTORY_SLOT_CONSUMABLE), data.xpos - 2, data.ypos - 2, data.width + 4, data.height + 4, 0);
		Item* i = *data.item_slot;
		if (i != nullptr)
			i->Draw(data.xpos, data.ypos, data.width, data.height);
		break;
	}
	case SLOT_DISPLAY_CONFIGURATION_TYPE::PLACEABLE:
	{
		al_draw_scaled_bitmap(INVENTORY_SLOT_PLACEABLE, 0, 0, al_get_bitmap_width(INVENTORY_SLOT_PLACEABLE), al_get_bitmap_height(INVENTORY_SLOT_PLACEABLE), data.xpos - 2, data.ypos - 2, data.width + 4, data.height + 4, 0);
		Item* i = *data.item_slot;
		if (i != nullptr)
			i->Draw(data.xpos, data.ypos, data.width, data.height);
		break;
	}
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
