#include "SimpleItemInventoryShovelToolStorageSlotUIComponent.h"
#include "ToolItem.h"

bool SimpleItemInventoryShovelToolStorageSlotUIComponent::ItemCheckPredicate() const
{
	if (!swapptr)
		return true;
	ToolItem* t = dynamic_cast<ToolItem*>(swapptr);
	if (t == nullptr)
		return false;
	return t->IsShovel();
}

SimpleItemInventoryShovelToolStorageSlotUIComponent::SimpleItemInventoryShovelToolStorageSlotUIComponent(int x, int y, int w, int h, ALLEGRO_BITMAP* b, Item*& i, Item*& s) : UIComponent(x, y, w, h), ItemInventoryStorageSlotUIComponent(x, y, w, h, b, i, s)
{}
