#include "InventoryGUI.h"
#include "ResourceLoader.h"
#include "SimpleItemInventoryCallbackSlotUIComponent.h"
#include "SimpleItemInventoryGenericStorageSlotUIComponent.h"
#include "SimpleItemInventoryViewStorageSlotUIComponent.h"


ALLEGRO_BITMAP* InventoryGUI::INVENTORY_SLOT_GENERIC;
ALLEGRO_BITMAP* InventoryGUI::INVENTORY_SLOT_CALLBACK;
ALLEGRO_BITMAP* InventoryGUI::INVENTORY_SLOT_TRASH;
ALLEGRO_BITMAP* InventoryGUI::INVENTORY_SLOT_SHOVEL;
ALLEGRO_BITMAP* InventoryGUI::INVENTORY_SLOT_PICKAXE;
ALLEGRO_BITMAP* InventoryGUI::INVENTORY_SLOT_AXE;
ALLEGRO_BITMAP* InventoryGUI::INVENTORY_SLOT_MELEE;
ALLEGRO_BITMAP* InventoryGUI::INVENTORY_SLOT_RANGED;
ALLEGRO_BITMAP* InventoryGUI::INVENTORY_SLOT_CONSUMABLE;
ALLEGRO_BITMAP* InventoryGUI::INVENTORY_SLOT_PLACEABLE;

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

void InventoryGUI::AddSlot(int x, int y, int w, int h, Item*& itemslot, StorageSlotType t)
{
	switch (t)
	{
	case StorageSlotType::VIEW:
		GUI::UIcomponents.push_back(new SimpleItemInventoryViewStorageSlotUIComponent(x, y, w, h, INVENTORY_SLOT_GENERIC, itemslot));
		break;
	default:
		GUI::UIcomponents.push_back(new SimpleItemInventoryGenericStorageSlotUIComponent(x, y, w, h, INVENTORY_SLOT_GENERIC, itemslot, swapTemp));
	}
}

void InventoryGUI::AddCallbackSlot(int x, int y, int w, int h, std::function<Item* (Item*)> cl, std::function<Item* (Item*)> cr)
{
	GUI::UIcomponents.push_back(new SimpleItemInventoryCallbackSlotUIComponent(x, y, w, h, INVENTORY_SLOT_CALLBACK, cl, cr, swapTemp));
}

void InventoryGUI::AddTrashSlot(int x, int y, int w, int h)
{
	static std::function<Item* (Item*)> callbackleft = [](Item* item) {
		if (item == nullptr)
			return (Item*)nullptr;
		item->RemoveAmount(1);
		if (item->GetAmount() <= 0)
		{
			delete item;
			return (Item*)nullptr;
		}
		return item;
	};
	static std::function<Item* (Item*)> callbackright = [](Item* item) {
		if (item != nullptr)
			delete item;
		return nullptr;
	};
	GUI::UIcomponents.push_back(new SimpleItemInventoryCallbackSlotUIComponent(x, y, w, h, INVENTORY_SLOT_TRASH, callbackleft, callbackright, swapTemp));
}

InventoryGUI::InventoryGUI() : swapTemp{ nullptr }
{
}

void InventoryGUI::Init()
{
	INVENTORY_SLOT_GENERIC = loaded_bitmaps["tex.gui.inventory_slot"];
	INVENTORY_SLOT_CALLBACK = loaded_bitmaps["tex.gui.inventory_slot_function"];
	INVENTORY_SLOT_TRASH = loaded_bitmaps["tex.gui.inventory_slot_trash"];
	INVENTORY_SLOT_SHOVEL = loaded_bitmaps["tex.gui.inventory_slot_shovel"];
	INVENTORY_SLOT_PICKAXE = loaded_bitmaps["tex.gui.inventory_slot_pickaxe"];
	INVENTORY_SLOT_AXE = loaded_bitmaps["tex.gui.inventory_slot_axe"];
	INVENTORY_SLOT_MELEE = loaded_bitmaps["tex.gui.inventory_slot_melee"];
	INVENTORY_SLOT_RANGED = loaded_bitmaps["tex.gui.inventory_slot_ranged"];
	INVENTORY_SLOT_CONSUMABLE = loaded_bitmaps["tex.gui.inventory_slot_consumable"];
	INVENTORY_SLOT_PLACEABLE = loaded_bitmaps["tex.gui.inventory_slot_placeable"];
}

void InventoryGUI::PreDrawThisGUI()
{

}


void InventoryGUI::PostDrawThisGUI()
{
	int x, y;
	al_get_mouse_cursor_position(&x, &y);
	if (swapTemp != nullptr)
		swapTemp->Draw(x - 64, y - 64, 128, 128);
}

