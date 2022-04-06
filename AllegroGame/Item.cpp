#include "Item.h"
#include "StoneItem.h"
#include "DirtItem.h"
#include "StickItem.h"
#include "SandItem.h"
#include "ResourceLoader.h"
#include "World.h"
#include <allegro5/allegro_font.h>

Item::Item(std::string n) : name{ n }, amount{ 1 }
{}

void Item::LoadAdditionalDataFromFile(std::ifstream &file)
{
    return;
}

void Item::WriteAdditionalDataToFile(std::ofstream& file)
{
    return;
}

std::string Item::GetName() const
{
    return name;
}

int Item::GetAmount() const
{
    return amount;
}

int Item::RemoveAmount(int targetAmount)
{
    int removeAmount = std::min(targetAmount, amount);
    amount -= removeAmount;
    return removeAmount;
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
    if (item == nullptr)
        return false;
    return item->GetID()==GetID();
}

int Item::AddAmount(int a)
{
    amount += a;
    if (amount > MAX_AMOUNT)
    {
        int tmp = amount - MAX_AMOUNT;
        amount = MAX_AMOUNT;
        return tmp;
    }
    return 0;
}

void Item::UseOnTile(World* world, int x, int y)
{
    return;
}

Item* MakeItemFromID(std::string id)
{
    if (id == DirtItem::ID)
        return new DirtItem();
    if (id == StoneItem::ID)
        return new StoneItem();
    if (id == StickItem::ID)
        return new StickItem();
    if (id == SandItem::ID)
        return new SandItem();
    return nullptr;
}

Item* MakeItemFromJSON(nlohmann::json data)
{
    Item* item = MakeItemFromID(data["id"]);
    if(item==nullptr)
        return nullptr;
    item->SetAmount(data["amount"]);
    return item;
}
