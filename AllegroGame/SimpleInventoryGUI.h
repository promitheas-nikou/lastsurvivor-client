#pragma once
#include "InventoryGUI.h"

#include "ItemInventory.h"

class SimpleInventoryGUI :
    public InventoryGUI
{
private:
    
    ItemInventory* inventory;

protected:
    
    Item* GetItem(int itemID) override;
    void SetItem(int itemID, Item* temp) override;
public:

    SimpleInventoryGUI(ItemInventory* inv);

    virtual ~SimpleInventoryGUI() = default;
};

