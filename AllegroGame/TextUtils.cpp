#include "TextUtils.h"
#include <allegro5/allegro_primitives.h>

void TextUtils::DrawText(ALLEGRO_FONT* font, int x, int y, const char* text, ALLEGRO_COLOR color)
{
	al_draw_text(font, color, x, y, 0, text);
}

void TextUtils::DrawCenteredText(ALLEGRO_FONT* font, int x, int y, const char* text, ALLEGRO_COLOR color)
{
	int w = al_get_text_width(font, text);
	al_draw_text(font, color, x - w / 2, y, 0, text);
}

void TextUtils::DrawTextWithBackground(ALLEGRO_FONT* font, int x, int y, const char* text, ALLEGRO_COLOR text_color, ALLEGRO_COLOR background_color)
{
	int bbx, bby;
	int w, h;
	al_get_text_dimensions(font, text, &bbx, &bby, &w, &h);
	al_draw_filled_rectangle(x, y, x + w, y + h, background_color);
	al_draw_text(font, text_color, x, y, 0, text);
}

void TextUtils::DrawCenteredTextWithBackground(ALLEGRO_FONT* font, int x, int y, const char* text, ALLEGRO_COLOR text_color, ALLEGRO_COLOR background_color)
{
	int bbx, bby;
	int w, h;
	al_get_text_dimensions(font, text, &bbx, &bby, &w, &h);
	al_draw_filled_rectangle(x-w/2, y, x + w/2, y + h, background_color);
	al_draw_text(font, text_color, x-w/2, y, 0, text);
}
