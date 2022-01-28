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

void Item::Draw(int x, int y, int width, int height) const
{
    ALLEGRO_BITMAP* tex = GetTexture();
    al_draw_scaled_bitmap(tex, 0, 0, al_get_bitmap_width(tex), al_get_bitmap_height(tex), x, y, width, height, 0);
    al_draw_textf(loaded_fonts[1][30], al_map_rgb(255, 0, 0), x + width - 40, y + height - 40, 0, "%d", GetAmount());
}

Item* MakeItem(int id)
{
    switch (id)
    {
    case StoneItem::ID:
        return new StoneItem();
    case DirtItem::ID:
        return new DirtItem();
    }
}
