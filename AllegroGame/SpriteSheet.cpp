#include "SpriteSheet.h"

void SpriteSheet::SetTargetBitmap(ALLEGRO_BITMAP* new_bmp)
{
	bmp = new_bmp;
}

ALLEGRO_BITMAP* SpriteSheet::GetTargetBitmap() const
{
	return bmp;
}

SpriteSheet::SpriteSheet(ALLEGRO_BITMAP* bitmap, int width, int height)
{
	bmp = bitmap;
	sw = width;
	sh = height;
	row = al_get_bitmap_width(bmp) / width;
	col = al_get_bitmap_height(bmp) / height;
}

void SpriteSheet::Draw(int x, int y, int width, int height, float r, int texID) const
{
	al_draw_tinted_scaled_rotated_bitmap_region(bmp, (texID % col) * sw, (texID / col) * sh, sw, sh, al_map_rgba(255, 255, 255, 255), sw / 2.f, sh / 2.f, x, y, width/(float)sw, height/(float)sh, r, 0);
}

void SpriteSheet::Draw(int x, int y, int width, int height, int texID) const
{
	Draw(x, y, width, height, 0.f, texID);
}

void SpriteSheet::Draw(int x, int y, int texID) const
{
	Draw(x, y, sw, sh, texID);
}
