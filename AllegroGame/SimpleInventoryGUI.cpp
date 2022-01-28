#include "SimpleInventoryGUI.h"

Item* SimpleInventoryGUI::GetItem(int itemID)
{
    return inventory->GetItem(itemID);
}

void SimpleInventoryGUI::SetItem(int itemID, Item* temp)
{
    inventory->SetItem(itemID, temp);
}

SimpleInventoryGUI::SimpleInventoryGUI(ItemInventory* inv) : InventoryGUI(), inventory{ inv }
{}
