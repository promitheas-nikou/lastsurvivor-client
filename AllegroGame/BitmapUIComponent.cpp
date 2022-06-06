#include "BitmapUIComponent.h"

BitmapUIComponent::BitmapUIComponent(ALLEGRO_BITMAP* b) : bitmap{ b }
{}

void BitmapUIComponent::Draw()
{
	al_draw_scaled_bitmap(bitmap, 0, 0, al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap), 0, 0, GetWidth(), GetHeight(), 0);
}
