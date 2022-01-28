#include "ItemInventory.h"

int ItemInventory::AddItemToSlot(Item* item, int itemID)
{
    Item* tmp = GetItem(itemID);
    if (tmp == nullptr)
    {
        SetItem(itemID, item);
        return 0;
    }
    if (tmp->GetID() == item->GetID())
        return tmp->AddAmount(item->GetAmount());
    return item->GetAmount();
}

Item* ItemInventory::AddItem(Item* item)
{
    if (item == nullptr)
        nullptr;
    for (int i = 0; (i < GetSize())&&(item->GetAmount()); i++)
    {
        if (GetItem(i) != nullptr)
        {
            if(GetItem(i)->Equals(item))
                item->SetAmount(GetItem(i)->AddAmount(item->GetAmount()));
        }
        else
        {
            Item* newItem;
            SetItem(i, item);
            return nullptr;
        }
    }
}
