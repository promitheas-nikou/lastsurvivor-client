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
#include "SimpleItemBundle.h"

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

Item* Item::SetAmount(int a)
{
    amount = a;
    return this;
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

void Item::DrawItemDetailsPane(int x, int y)
{
    std::string id = ("#" + GetID());
    int w1 = al_get_text_width(loaded_fonts["default"][30], GetName().c_str());
    int w2 = al_get_text_width(loaded_fonts["default"][20], id.c_str());
    int w = w1 + w2;
    al_draw_filled_rectangle(x, y, x + w + 25, y + 50, al_map_rgba(10, 30, 50, 200));
    al_draw_text(loaded_fonts["default"][30], al_map_rgba(255, 255, 255, 255), x + 10, y + 10, 0, GetName().c_str());
    al_draw_text(loaded_fonts["default"][20], al_map_rgba(150, 150, 150, 255), x + w1 + 15, y + 20, 0, id.c_str());
}

ItemBundle* Item::ConstCollapseToItemBundle() const
{
    SimpleItemBundle* b = new SimpleItemBundle();
    b->AddItem(this->Clone());
    return b;
}

void Item::AddConstToInventory(ItemInventory* inv) const
{
    inv->AddConstItem(this);
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
