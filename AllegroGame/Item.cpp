#include "Item.h"
#include "StoneItem.h"
#include "DirtItem.h"
#include "ResourceLoader.h"
#include <allegro5/allegro_font.h>

Item::Item(std::string n) : name{ n }, amount{ 1 }
{}

std::string Item::GetName() const
{
    return name;
}

int Item::GetAmount() const
{
    return amount;
}

void Item::SetAmount(int a)
{
    amount = a;
}

bool Item::Equals(const Item& item) const
{
    return Equals(&item);
}

bool Item::Equals(const Item* item) const
{
    return item->GetID()==GetID();
}

constexpr int STACK_SIZE = 24;

int Item::AddAmount(int a)
{
    amount += a;
    if (amount > STACK_SIZE)
    {
        int tmp = amount - STACK_SIZE;
        amount = STACK_SIZE;
        return tmp;
    }
    return 0;
}

Item* MakeItem(std::string id)
{
    if (id == DirtItem::ID)
        return new DirtItem();
    if (id == StoneItem::ID)
        return new StoneItem();
}
