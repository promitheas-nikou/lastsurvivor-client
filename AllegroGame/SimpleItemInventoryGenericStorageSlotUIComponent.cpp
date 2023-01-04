#include "SimpleItemInventoryGenericStorageSlotUIComponent.h"

bool SimpleItemInventoryGenericStorageSlotUIComponent::ItemCheckPredicate() const
{
    return true;
}

SimpleItemInventoryGenericStorageSlotUIComponent::SimpleItemInventoryGenericStorageSlotUIComponent(int x, int y, int w, int h, ALLEGRO_BITMAP* b, Item*& i, Item*& s) : UIComponent(x, y, w, h), ItemInventoryStorageSlotUIComponent(x, y, w, h, b, i, s)
{}