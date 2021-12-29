#include "SimpleUIComponent.h"
#include <allegro5/allegro_primitives.h>
#include <cstdio>

SimpleUIComponent::SimpleUIComponent(ALLEGRO_BITMAP* t) : texture{ t }
{}

void SimpleUIComponent::Draw()
{
    al_draw_scaled_bitmap(texture, 0, 0, al_get_bitmap_width(texture), al_get_bitmap_height(texture), 0, 0, width, height, 0);
}


