#include "Item.h"
#include "StoneItem.h"
#include "DirtItem.h"
#include "StickItem.h"
#include "SandItem.h"
#include "BerryItem.h"
#include "SimpleSword.h"
#include "GunItem.h"
#include "ResourceLoader.h"
#include "World.h"
#include <allegro5/allegro_font.h>
#include "Config.h"

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

void Item::DrawText(int x, int y, ALLEGRO_FONT* font, ALLEGRO_COLOR color, int align) const
{
    al_draw_textf(font, color, x, y, align, "%d x %s", GetAmount(), GetName().c_str());
}

void Item::DrawWithText(int x, int y, int width, int height) const
{
    Draw(x, y, width, height);
    DrawText(x + width, y + width / 2 - 20, loaded_fonts["default"][30], gameconfig::SOLID_TEXT_COLOR_NORMAL, 0);
}

std::unordered_map<std::string, Item*> prototype_items;

Item* MakeItemFromID(std::string id)
{
    Item* p = prototype_items[id];
    return (p == nullptr) ? nullptr : p->Clone();
}

Item* MakeItemFromJSON(nlohmann::json data)
{
    Item* item = MakeItemFromID(data["id"]);
    if(item==nullptr)
        return nullptr;
    item->SetAmount(data["amount"]);
    return item;
}
