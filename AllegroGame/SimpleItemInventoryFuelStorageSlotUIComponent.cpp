#include "SimpleItemInventoryFuelStorageSlotUIComponent.h"
#include "FuelItem.h"
#include "GUI.h"
#include "PlayerEntity.h"

bool SimpleItemInventoryFuelStorageSlotUIComponent::ItemCheckPredicate() const
{
    Item*& swapptr = GUI_GLOBAL_PLAYER_OBJECT->GetStashedItem();
	if (!swapptr)
		return true;
	return dynamic_cast<FuelItem*>(swapptr) != nullptr;
}

SimpleItemInventoryFuelStorageSlotUIComponent::SimpleItemInventoryFuelStorageSlotUIComponent(int x, int y, int w, int h, ALLEGRO_BITMAP* b, Item*& i, Item*& s) : UIComponent(x, y, w, h), ItemInventoryStorageSlotUIComponent(x, y, w, h, b, i, s)
{}