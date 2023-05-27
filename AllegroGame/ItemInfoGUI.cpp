#include "ItemInfoGUI.h"
#include "Config.h"
#include "Graphics.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "ResourceLoader.h"

void ItemInfoGUI::SetTargetItem(const Item* i)
{
	item = i;
}

bool ItemInfoGUI::KeyDown(ALLEGRO_KEYBOARD_EVENT& event)
{
	return false;
}

int lastLine = 0;
bool _iteminfogui_text_callback(int num_line, const char* line, int size, void* extra) {
	lastLine = num_line;
	return true;
}

void ItemInfoGUI::PreDrawThisGUI()
{
	al_draw_filled_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, gameconfig::SOLID_BACKGROUND_COLOR_2);
	al_draw_filled_rectangle(200, 200, SCREEN_WIDTH - 200, SCREEN_HEIGHT - 200, gameconfig::SOLID_BACKGROUND_COLOR_0);
	al_draw_filled_rectangle(216, 216, 472, 472, gameconfig::SOLID_BACKGROUND_COLOR_0);
	item->Draw(216, 216, 256, 256);
	item->DrawText(477, 221, game_GetFont("default", 50), gameconfig::SOLID_TEXT_COLOR_NORMAL, 0);
	al_do_multiline_text(game_GetFont("default", 30), SCREEN_WIDTH - 420, item->GetDescription().c_str(), &_iteminfogui_text_callback, nullptr);
	al_draw_multiline_text(game_GetFont("default", 20), gameconfig::SOLID_TEXT_COLOR_NORMAL, 210, 480, SCREEN_WIDTH - 420, 22, 0, item->GetDescription().c_str());
}

void ItemInfoGUI::PostDrawThisGUI()
{
}
