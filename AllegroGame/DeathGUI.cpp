#include "DeathGUI.h"
#include "SimpleButtonUIComponent.h"
#include "Graphics.h"
#include "ResourceLoader.h"
#include "PlayerEntity.h"
#include <allegro5/allegro_primitives.h>

PlayerEntity* player;

void deathguicallback()
{
	player->ResetAfterDeath();
}

DeathGUI::DeathGUI(PlayerEntity* p) : TEXTURE{ loaded_bitmaps["tex.gui.death"] }
{
	player = p;
	UIcomponents.push_back(new SimpleButtonUIComponent(SCREEN_WIDTH / 2 - 512, SCREEN_HEIGHT / 2 - 256, 1024, 512, loaded_bitmaps["tex.gui.death"], &deathguicallback));
}

void DeathGUI::PreDrawThisGUI()
{
	al_draw_filled_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, al_map_rgba(255,0,0,100));
}

void DeathGUI::PostDrawThisGUI()
{

}
