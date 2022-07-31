#include "FuelItem.h"
#include "ResourceLoader.h"
#include <allegro5/allegro_primitives.h>
#include "Config.h"

FuelItem::FuelItem(std::string name, std::string description) : Item(name, description)
{}

void FuelItem::DrawItemDetailsPane(int x, int y) {
	std::string id = ("#" + GetID());
	int w1 = al_get_text_width(loaded_fonts["default"][30], GetName().c_str());
	int w2 = al_get_text_width(loaded_fonts["default"][20], id.c_str());
	int w3 = al_get_text_width(loaded_fonts["default"][20], GetDescription().c_str());
	int w = std::max(300, std::max(w1 + w2, w3 / 5));

	MLBUF = 0;
	al_do_multiline_text(loaded_fonts["default"][20], w, GetDescription().c_str(), &DrawItemDetailsPaneMultilineCB, NULL);
	int h = (MLBUF + 1) * 23 + 97;
	al_draw_filled_rectangle(x, y, x + w + 25, y + h, al_map_rgba(10, 30, 50, 200));
	al_draw_textf(loaded_fonts["default"][20], gameconfig::SOLID_TEXT_COLOR_ERROR, x + 15, y + 45, 0, "Burn Time: %.1f s", GetBurnTime());
	al_draw_textf(loaded_fonts["default"][20], gameconfig::SOLID_TEXT_COLOR_ERROR, x + 15, y + 67, 0, "Burn Heat: %.1f C", GetBurnHeat());
	//al_draw_textf(loaded_fonts["default"][20], b2 ? gameconfig::SOLID_TEXT_COLOR_OK : gameconfig::SOLID_TEXT_COLOR_ERROR, x + 15, y + 67, 0, "Water: %c%.1f", b2 ? '+' : '-', );
	al_draw_text(loaded_fonts["default"][30], al_map_rgba(255, 255, 255, 255), x + 10, y + 10, 0, GetName().c_str());
	al_draw_text(loaded_fonts["default"][20], al_map_rgba(150, 150, 150, 255), x + w1 + 15, y + 20, 0, id.c_str());
	al_draw_multiline_text(loaded_fonts["default"][20], al_map_rgba(255, 255, 255, 255), x + 10, y + 89, w, 23, 0, GetDescription().c_str());
}