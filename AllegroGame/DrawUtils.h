#pragma once
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#define DRAW_UTILS_WRITE_PERCENTAGE_NUMBER_FORMAT_FLOAT 0b0
#define DRAW_UTILS_WRITE_PERCENTAGE_NUMBER_FORMAT_PERCENT 0b1
#define DRAW_UTILS_WRITE_PERCENTAGE_NUMBER_FORMAT_FLOAT_RELATIVE 0b10
#define DRAW_UTILS_WRITE_PERCENTAGE_NUMBER_FORMAT_PERCENT_RELATIVE 0b11
#define DRAW_UTILS_WRITE_PERCENTAGE_NUMBER_FORMAT_FLOAT_RATIO 0b100

namespace DrawUtils
{
	void DrawProgressBar(float x1, float y1, float x2, float y2, ALLEGRO_COLOR back_color, ALLEGRO_COLOR fill_color, float val, int flags);
	void DrawProgressBarWriteValue(float x1, float y1, float x2, float y2, ALLEGRO_COLOR back_color, ALLEGRO_COLOR fill_color, ALLEGRO_FONT* font, ALLEGRO_COLOR text_color, int flags, float val, float totalval);
};

