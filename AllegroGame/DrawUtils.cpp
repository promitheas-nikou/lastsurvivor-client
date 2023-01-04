#include "DrawUtils.h"
#include <allegro5/allegro_primitives.h>
#include <string.h>
#include <stdio.h>

void DrawUtils::DrawProgressBar(float x1, float y1, float x2, float y2, ALLEGRO_COLOR back_color, ALLEGRO_COLOR fill_color, float val, int flags)
{
	float mid = x1 + (x2 - x1) * val;
	al_draw_filled_rectangle(x1, y1, mid, y2, back_color);
	al_draw_filled_rectangle(mid, y1, x2, y2, fill_color);
}

void DrawUtils::DrawProgressBarWriteValue(float x1, float y1, float x2, float y2, ALLEGRO_COLOR back_color, ALLEGRO_COLOR fill_color, ALLEGRO_FONT* font, ALLEGRO_COLOR text_color, int flags, float val, float totalval)
{
	DrawProgressBar(x1, y1, x2, y2, back_color, fill_color, val/totalval, flags);
	char txt[10];
	switch (flags) {
	case DRAW_UTILS_WRITE_PERCENTAGE_NUMBER_FORMAT_PERCENT:
		sprintf(txt, "%.1f%%", 100*val);
		break;
	case DRAW_UTILS_WRITE_PERCENTAGE_NUMBER_FORMAT_FLOAT:
		sprintf(txt, "%.3f", val);
		break;
		case DRAW_UTILS_WRITE_PERCENTAGE_NUMBER_FORMAT_PERCENT_RELATIVE:
		sprintf(txt, "%.1f%%", 100*val / totalval);
		break;
	case DRAW_UTILS_WRITE_PERCENTAGE_NUMBER_FORMAT_FLOAT_RELATIVE:
		sprintf(txt, "%.3f", val / totalval);
		break;	
	case DRAW_UTILS_WRITE_PERCENTAGE_NUMBER_FORMAT_FLOAT_RATIO:
		sprintf(txt, "%.1f/%.1f", val, totalval);
		break;	
	}
	al_draw_text(font, text_color, (x1 + x2) / 2, y1, ALLEGRO_ALIGN_CENTER, txt);
}
