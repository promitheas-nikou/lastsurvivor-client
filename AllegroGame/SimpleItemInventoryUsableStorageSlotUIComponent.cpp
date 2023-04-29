#include "SimpleItemInventoryUsableStorageSlotUIComponent.h"
#include "UsableItem.h"
#include "GUI.h"
#include "PlayerEntity.h"


bool SimpleItemInventoryUsableStorageSlotUIComponent::ItemCheckPredicate() const
{
	Item*& swapptr = GUI_GLOBAL_PLAYER_OBJECT->GetStashedItem();
	if (!swapptr)
		return true;
    return dynamic_cast<UsableItem*>(swapptr) != nullptr;
}

SimpleItemInventoryUsableStorageSlotUIComponent::SimpleItemInventoryUsableStorageSlotUIComponent(int x, int y, int w, int h, ALLEGRO_BITMAP* b, Item*& i, Item*& s) : UIComponent(x,y,w,h), ItemInventoryStorageSlotUIComponent(x,y,w,h,b,i,s)
{}