#include "ItemInventory.h"
#include "ItemBundle.h"
#include "ItemIndex.h"
#include "SimpleItemInventory.h"
#include "SimpleItemBundle.h"

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

void ItemInventory::AddConstItem(const Item* item)
{
    if (item == nullptr)
        return;
    delete AddItem(item->Clone());
}

bool ItemInventory::CanAddConstItem(const Item* item)
{
    int amount = item->GetAmount();
    Item* tmp;
    for (int i = 0; i < GetSize(); i++)
    {
        tmp = GetItem(i);
        if (tmp == nullptr)
            return true;
        if (item->Equals(tmp))
            amount -= tmp->GetMaxStackSize() - tmp->GetAmount();
        if (amount <= 0)
            return true;
    }
    return false;
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

bool ItemInventory::ContainsItemIndexItems(const ItemIndex* i) const
{
    ItemIndex* a = new ItemIndex(this);
    bool val = a->CheckGreaterThan(i);
    delete a;
    return val;
}

int ItemInventory::CountTimesContainsItem(const Item* item) const
{
    SimpleItemBundle b;
    b.AddItem(const_cast<Item*>(item));
    return CountTimesContainsItemBundleItems(&b);
}

int ItemInventory::CountTimesContainsItemBundleItems(const ItemBundle* bundle) const
{
    ItemIndex i1(bundle);
    ItemIndex i2(this);
    return i2.GetMaxFactor(&i1);
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

Item* ItemInventory::PullItem()
{
    Item* r;
    for(int i=0;i<GetSize();i++)
        if (r = GetItem(i))
        {
            SetItem(i, nullptr);
            return r;
        }
    return nullptr;
}

void ItemInventory::SaveToFile(std::ostream& file)
{
    uint32_t v;
    constexpr uint32_t nullitemid = 0xFFFFFFFF;
    v = GetSize();
    file.write(reinterpret_cast<char*>(&v), sizeof(uint32_t));
    for (int i = 0; i < v; i++)
    {
        Item* t = GetItem(i);
        if (t == nullptr)
            file.write(reinterpret_cast<const char*>(&nullitemid), sizeof(uint32_t));
        else
            t->SaveToFile(file);
        file.flush();
    }
}

ItemInventory* ItemInventory::LoadFromFile(std::istream& file)
{
    uint32_t v;
    file.read(reinterpret_cast<char*>(&v), sizeof(uint32_t));
    SimpleItemInventory* inv = new SimpleItemInventory(v);
    for (int i = 0; i < v; i++)
    {
        inv->SetItem(i, Item::LoadFromFile(file));
    }
    return inv;
}

