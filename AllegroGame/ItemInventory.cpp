#include "ItemInventory.h"
#include "ItemBundle.h"
#include "ItemIndex.h"

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

void ItemInventory::AddConstItem(Item* item)
{
    if (item == nullptr)
        return;
    AddItem(item->Clone());
}

Item* ItemInventory::AddItem(Item* item)
{
    if (item == nullptr)
        return nullptr;
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
    if (item->GetAmount() == 0)
    {
        delete item;
        return nullptr;
    }
    return item;
}

void ItemInventory::AddConstItemBundle(const ItemBundle* bundle)
{
    if (bundle == nullptr)
        return;
    bundle->AddConstToInventory(this);
}

bool ItemInventory::ContainsItem(const Item* item) const
{
    if (item == nullptr)
        return true;
    int amount = 0;
    for (int i = 0; i < GetSize(); i++)
    {
        if (item->Equals(GetItem(i)))
            amount += GetItem(i)->GetAmount();
        if (amount >= item->GetAmount())
            return true;
    }
    return amount >= item->GetAmount();
}

bool ItemInventory::ContainsItemBundleItems(const ItemBundle* bundle) const
{
    ItemIndex* a;
    ItemIndex* b;
    a = new ItemIndex(this);
    b = new ItemIndex(bundle);
    bool val = a->CheckGreaterThan(b);
    delete a;
    delete b;
    return val;
}

void ItemInventory::RemoveConstItem(const Item* item)
{
    int amount = item->GetAmount();
    for (int i = 0; i < GetSize(); i++)
    {
        Item* tmp = GetItem(i);
        if (tmp == nullptr)
            continue;
        if (tmp->GetID() == item->GetID())
        {
            amount -= tmp->RemoveAmount(amount);
            if (tmp->GetAmount() == 0)
                SetItem(i, nullptr);
        }
        if (amount == 0)
            return;
    }
    return;
}

void ItemInventory::RemoveConstItemBundle(const ItemBundle* bundle)
{
    for (int i = 0; i < bundle->GetSize(); i++)
        RemoveConstItem(bundle->GetItem(i));
}

ItemBundle* ItemInventory::AddItemBundle(ItemBundle* bundle)
{
    if (bundle == nullptr)
        return nullptr;
    return bundle->AddToInventory(this);
}

