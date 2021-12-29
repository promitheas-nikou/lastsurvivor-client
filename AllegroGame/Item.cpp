#include "Item.h"

Item::Item(std::string n) : name(n)
{}

std::string Item::GetName() const
{
    return name;
}

void Item::Draw(int x, int y, int width, int height) const
{
    ALLEGRO_BITMAP* tex = GetTexture();
    al_draw_scaled_bitmap(tex, 0, 0, al_get_bitmap_width(tex), al_get_bitmap_height(tex), x, y, width, height, 0);
}

Item* MakeItem(int id)
{
    return nullptr;
}
