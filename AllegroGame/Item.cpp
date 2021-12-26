#include "Item.h"

Item::Item(std::string n) : name(n)
{}

std::string Item::GetName() const
{
    return name;
}

Item* MakeItem(int id)
{
    return nullptr;
}
