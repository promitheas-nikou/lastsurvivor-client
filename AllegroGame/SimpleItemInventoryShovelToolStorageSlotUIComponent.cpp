#include "SimpleItemInventoryShovelToolStorageSlotUIComponent.h"
#include "ToolItem.h"
#include "GUI.h"
#include "PlayerEntity.h"

bool SimpleItemInventoryShovelToolStorageSlotUIComponent::ItemCheckPredicate() const
{
	Item*& swapptr = GUI_GLOBAL_PLAYER_OBJECT->GetStashedItem();
	if (!swapptr)
		return true;
	ToolItem* t = dynamic_cast<ToolItem*>(swapptr);
	if (t == nullptr)
		return false;
	return t->IsShovel();
}

SimpleItemInventoryShovelToolStorageSlotUIComponent::SimpleItemInventoryShovelToolStorageSlotUIComponent(int x, int y, int w, int h, ALLEGRO_BITMAP* b, Item*& i, Item*& s) : UIComponent(x, y, w, h), ItemInventoryStorageSlotUIComponent(x, y, w, h, b, i, s)
{}
