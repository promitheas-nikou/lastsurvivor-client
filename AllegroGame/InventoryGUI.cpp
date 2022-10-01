#include "InventoryGUI.h"
#include "ResourceLoader.h"
#include "SimpleItemInventoryCallbackSlotUIComponent.h"
#include "SimpleItemInventoryGenericStorageSlotUIComponent.h"
#include "SimpleItemInventoryPlaceableStorageSlotUIComponent.h"
#include "SimpleItemInventoryConsumableStorageSlotUIComponent.h"
#include "SimpleItemInventoryUsableStorageSlotUIComponent.h"
#include "SimpleItemInventoryFuelStorageSlotUIComponent.h"
#include "SimpleItemInventoryViewStorageSlotUIComponent.h"
#include "SimpleDynamicItemInventoryGenericStorageSlotUIComponent.h"
#include "SimpleDynamicItemInventoryFuelStorageSlotUIComponent.h"
#include "SimpleDynamicItemInventoryOutputStorageSlotUIComponent.h"


ALLEGRO_BITMAP* InventoryGUI::INVENTORY_SLOT_GENERIC;
ALLEGRO_BITMAP* InventoryGUI::INVENTORY_SLOT_CALLBACK;
ALLEGRO_BITMAP* InventoryGUI::INVENTORY_SLOT_TRASH;
ALLEGRO_BITMAP* InventoryGUI::INVENTORY_SLOT_SHOVEL;
ALLEGRO_BITMAP* InventoryGUI::INVENTORY_SLOT_PICKAXE;
ALLEGRO_BITMAP* InventoryGUI::INVENTORY_SLOT_AXE;
ALLEGRO_BITMAP* InventoryGUI::INVENTORY_SLOT_MELEE;
ALLEGRO_BITMAP* InventoryGUI::INVENTORY_SLOT_RANGED;
ALLEGRO_BITMAP* InventoryGUI::INVENTORY_SLOT_CONSUMABLE;
ALLEGRO_BITMAP* InventoryGUI::INVENTORY_SLOT_USABLE;
ALLEGRO_BITMAP* InventoryGUI::INVENTORY_SLOT_PLACEABLE;

bool InventoryGUI::HandleEvent(ALLEGRO_EVENT& event)
{
	if (activeSubGUI != nullptr)
		if (activeSubGUI->HandleEvent(event))
			return true;
	ALLEGRO_MOUSE_STATE state;
	al_get_mouse_state(&state);
	if (selectedComponent != nullptr)
		switch (event.type) {
		case ALLEGRO_EVENT_KEY_DOWN:
			return selectedComponent->KeyDown(event.keyboard);
		case ALLEGRO_EVENT_KEY_UP:
			return selectedComponent->KeyUp(event.keyboard);
		case ALLEGRO_EVENT_KEY_CHAR:
			return selectedComponent->KeyChar(event.keyboard);
		}
	for (int i = 0; i < UIcomponents.size(); i++)
	{
		UIComponent* tmp = UIcomponents[i];

		if (tmp->ContainsPoint(state.x - xoffset, state.y - yoffset))
		{
			switch (event.type)
			{
			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
				selectedComponent = tmp;
				switch (event.mouse.button)
				{
				case 1:
					if (tmp->ClickLeftDown(event.mouse.x - xoffset, event.mouse.y - yoffset))
						return true;
					break;
				case 2:
					if (tmp->ClickRightDown(event.mouse.x - xoffset, event.mouse.y - yoffset))
						return true;
					break;
				}
				break;
			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				switch (event.mouse.button)
				{
				case 1:
					if (tmp->ClickLeftUp(event.mouse.x - xoffset, event.mouse.y - yoffset))
						return true;
					break;
				case 2:
					if (tmp->ClickRightUp(event.mouse.x - xoffset, event.mouse.y - yoffset))
						return true;
					break;
				}
				break;
			case ALLEGRO_EVENT_MOUSE_AXES: //MOUSE MOVED
				if (tmp->Hover(state.x - xoffset, state.y - xoffset))
					return true;
				break;
				//		case ALLEGRO_EVENT_KEY_CHAR:
				//			break;
			case ALLEGRO_EVENT_KEY_DOWN:
				return this->KeyDown(event.keyboard);
				break;
			case ALLEGRO_EVENT_KEY_UP:
				return this->KeyUp(event.keyboard);
				break;
			case ALLEGRO_EVENT_KEY_CHAR:
				return this->KeyChar(event.keyboard);
				break;
			}
		}
	}
	switch (event.type)
	{
	case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		if (this->MouseButtonDown(event.mouse))
			return true;
		break;
	case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
		if (this->MouseButtonUp(event.mouse))
			return true;
		break;
	case ALLEGRO_EVENT_MOUSE_AXES: //MOUSE MOVED
		if (this->MouseButtonMove(event.mouse))
			return true;
		break;
	case ALLEGRO_EVENT_KEY_CHAR:
		if (IsTyping() && this->KeyChar(event.keyboard))
			return true;
		break;
	case ALLEGRO_EVENT_KEY_DOWN:
		if (!IsTyping() && this->KeyDown(event.keyboard))
			return true;
		break;
	case ALLEGRO_EVENT_KEY_UP:
		if (!IsTyping() && this->KeyUp(event.keyboard))
			return true;
		break;
	}
	return false;
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

void InventoryGUI::AddSlot(int x, int y, int w, int h, Item*& itemslot, StorageSlotType t)
{
	switch (t)
	{
	case StorageSlotType::VIEW:
		GUI::UIcomponents.push_back(new SimpleItemInventoryViewStorageSlotUIComponent(x, y, w, h, INVENTORY_SLOT_GENERIC, itemslot));
		break;
	case StorageSlotType::PLACEABLE:
		GUI::UIcomponents.push_back(new SimpleItemInventoryPlaceableStorageSlotUIComponent(x, y, w, h, INVENTORY_SLOT_PLACEABLE, itemslot, swapTemp));
		break;
	case StorageSlotType::CONSUMABLE:
		GUI::UIcomponents.push_back(new SimpleItemInventoryConsumableStorageSlotUIComponent(x, y, w, h, INVENTORY_SLOT_CONSUMABLE, itemslot, swapTemp));
		break;
	case StorageSlotType::USABLE:
		GUI::UIcomponents.push_back(new SimpleItemInventoryUsableStorageSlotUIComponent(x, y, w, h, INVENTORY_SLOT_USABLE, itemslot, swapTemp));
		break;
	case StorageSlotType::FUEL:
		GUI::UIcomponents.push_back(new SimpleItemInventoryFuelStorageSlotUIComponent(x, y, w, h, INVENTORY_SLOT_GENERIC, itemslot, swapTemp));
		break;
	default:
		GUI::UIcomponents.push_back(new SimpleItemInventoryGenericStorageSlotUIComponent(x, y, w, h, INVENTORY_SLOT_GENERIC, itemslot, swapTemp));
	}
}

void InventoryGUI::AddDynamicSlot(int x, int y, int w, int h, std::function<Item**()> itemslotfunc, StorageSlotType t)
{
	switch (t)
	{
	case StorageSlotType::FUEL:
		GUI::UIcomponents.push_back(new SimpleDynamicItemInventoryFuelStorageSlotUIComponent(x, y, w, h, INVENTORY_SLOT_GENERIC, itemslotfunc, swapTemp));
		break;
	case StorageSlotType::OUTPUT:
		GUI::UIcomponents.push_back(new SimpleDynamicItemInventoryOutputStorageSlotUIComponent(x, y, w, h, INVENTORY_SLOT_GENERIC, itemslotfunc, swapTemp));
		break;
	default:
		GUI::UIcomponents.push_back(new SimpleDynamicItemInventoryGenericStorageSlotUIComponent(x, y, w, h, INVENTORY_SLOT_GENERIC, itemslotfunc, swapTemp));
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

void InventoryGUI::SetOffset(int xoff, int yoff)
{
	xoffset = xoff;
	yoffset = yoff;
}

InventoryGUI::InventoryGUI() : swapTemp{ nullptr }
{
}

int __CURRENT_OFFSET_X_GUI_INVENTORY_SLOT;
int __CURRENT_OFFSET_Y_GUI_INVENTORY_SLOT;

void InventoryGUI::DrawGUI()
{
	this->PreDrawThisGUI();

	ALLEGRO_TRANSFORM temp_gui_transform = *al_get_current_transform();
	__CURRENT_OFFSET_X_GUI_INVENTORY_SLOT = xoffset;
	__CURRENT_OFFSET_Y_GUI_INVENTORY_SLOT = yoffset;
	al_translate_transform(&temp_gui_transform, xoffset, yoffset);
	al_use_transform(&temp_gui_transform);
	for (int p = 1; p <= 3; p++)
		for (int i = 0; i < UIcomponents.size(); i++)
		{
			UIComponent* tmp = UIcomponents[i];
			al_translate_transform(&temp_gui_transform, tmp->GetXpos(), tmp->GetYpos());
			al_use_transform(&temp_gui_transform);
			UIcomponents[i]->Draw(p);
			al_translate_transform(&temp_gui_transform, -tmp->GetXpos(), -tmp->GetYpos());
		}
	al_use_transform(&temp_gui_transform);
	if (activeSubGUI != nullptr)
		activeSubGUI->DrawGUI();

	al_translate_transform(&temp_gui_transform, -xoffset, -yoffset);
	al_use_transform(&temp_gui_transform);

	this->PostDrawThisGUI();
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
	INVENTORY_SLOT_USABLE = loaded_bitmaps["tex.gui.inventory_slot_usable"];
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

