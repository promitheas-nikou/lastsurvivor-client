#pragma once
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

namespace TextUtils {

	void DrawText(ALLEGRO_FONT* font, int x, int y, const char* text, ALLEGRO_COLOR color);

	void DrawCenteredText(ALLEGRO_FONT* font, int x, int y, const char* text, ALLEGRO_COLOR color);

	void DrawTextWithBackground(ALLEGRO_FONT* font, int x, int y, const char* text, ALLEGRO_COLOR text_color, ALLEGRO_COLOR background_color);

	void DrawCenteredTextWithBackground(ALLEGRO_FONT* font, int x, int y, const char* text, ALLEGRO_COLOR text_color, ALLEGRO_COLOR background_color);
};
