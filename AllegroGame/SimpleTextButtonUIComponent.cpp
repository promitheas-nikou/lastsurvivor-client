#include "SimpleTextButtonUIComponent.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include "ResourceLoader.h"

void SimpleTextButtonUIComponent::Draw(int plane)
{
	if (plane != 1)
		return;
	al_draw_filled_rectangle(0, 0, GetWidth(), GetHeight(), background_color);
	al_draw_text(game_GetFont("default", 30), text_color, GetWidth() / 2, GetHeight() / 2 - 15, ALLEGRO_ALIGN_CENTER, text.c_str());
}

bool SimpleTextButtonUIComponent::ClickLeftUp(int xRel, int yRel)
{
	return true;
}

bool SimpleTextButtonUIComponent::Hover(int xRel, int yRel)
{
	return true;
}

bool SimpleTextButtonUIComponent::KeyDown(ALLEGRO_KEYBOARD_EVENT& evt)
{
	return false;
}

bool SimpleTextButtonUIComponent::KeyUp(ALLEGRO_KEYBOARD_EVENT& evt)
{
	return false;
}

bool SimpleTextButtonUIComponent::KeyChar(ALLEGRO_KEYBOARD_EVENT& evt)
{
	return false;
}

bool SimpleTextButtonUIComponent::ClickRightUp(int xRel, int yRel)
{
	return true;
}

bool SimpleTextButtonUIComponent::ClickRightDown(int xRel, int yRel)
{
	return true;
}

SimpleTextButtonUIComponent::SimpleTextButtonUIComponent(int x, int y, int w, int h, std::function<void(void)> cb, ALLEGRO_COLOR bc, ALLEGRO_COLOR tc, std::string txt) : UIComponent(x, y, w, h), ButtonUIComponent(cb), background_color{ bc }, text_color{ tc }, text{ txt }
{}
