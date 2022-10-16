#include "CreativeItemGUI.h"
#include "ResourceLoader.h"
#include "PlayerEntity.h"
#include "Config.h"
#include <algorithm>

void CreativeItemGUI::DrawItem(const Item* item, int x, int y, int tw, int th, int rw, int rh)
{
	al_draw_filled_rectangle(x, y, x + tw, y + th, gameconfig::SOLID_BACKGROUND_COLOR_0);
	item->Draw(x, y, rw, rh);
	item->DrawText(x + rw + 10, y + 10, loaded_fonts["default"][30], gameconfig::SOLID_TEXT_COLOR_NORMAL, ALLEGRO_ALIGN_LEFT);
}

void CreativeItemGUI::PreDrawThisGUI()
{
	al_draw_filled_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, gameconfig::TRANSPARENT_BACKGROUND_COLOR);
	al_draw_filled_rectangle(108, 108, SCREEN_WIDTH - 108, SCREEN_HEIGHT - 108, gameconfig::SOLID_BACKGROUND_COLOR_3);
	al_draw_filled_rectangle(128, 128, SCREEN_WIDTH - 128, SCREEN_HEIGHT - 128, gameconfig::SOLID_BACKGROUND_COLOR_1);
	for (int i = 0; i < std::min((unsigned long long) pageHeight, itemsList.size() - scroll); i++)
		DrawItem(itemsList[i + scroll], 148, 214 + i * 148, SCREEN_WIDTH - 296, 128, 128, 128);
}

void CreativeItemGUI::PostDrawThisGUI()
{

}

bool CreativeItemGUI::MouseButtonMove(ALLEGRO_MOUSE_EVENT& event)
{
	scroll -= event.dz;
	if (scroll < 0)
		scroll = 0;
	if (scroll > itemsList.size() - pageHeight)
		scroll = itemsList.size() - pageHeight;
	return true;
}

bool CreativeItemGUI::MouseButtonDown(ALLEGRO_MOUSE_EVENT& event)
{
	if ((event.x >= 148) && (event.x <= SCREEN_WIDTH - 148) && (event.y >= 214) && (event.y <= SCREEN_HEIGHT - 128))
	{
		int ind = ((event.y - 214) / 148) + scroll;
		if (ind < itemsList.size())
		{
			if (player)
				delete player->GiveItem(itemsList[ind]->Clone()->SetAmount((event.button==1)?1:-1));
		}
	}
	return true;
}

void CreativeItemGUI::SetCurrentPlayer(PlayerEntity* p)
{
	player = p;
}

void CreativeItemGUI::SetItemsList(std::unordered_map<std::string, Item*> i)
{
	itemsList.clear();
	for (const std::pair<std::string, Item*>& p : i)
		itemsList.push_back(p.second);
}

CreativeItemGUI::CreativeItemGUI(PlayerEntity* p, int pageHeight) : player{ p }, pageHeight { pageHeight }, scroll{ 0 }
{
}
