#include "SimpleToggleTextButtonUIComponent.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include "ResourceLoader.h"
#include "Config.h"

void SimpleToggleTextButtonUIComponent::Draw(int plane)
{
	if (plane != 1)
		return;
	al_draw_filled_rectangle(0, 0, GetWidth(), GetHeight(), background_color);
	al_draw_text(game_GetFont("default", 30), text_color, 10, GetHeight() / 2 - 15, ALLEGRO_ALIGN_LEFT, text.c_str());

	if(isToggled)
		al_draw_text(game_GetFont("default", 30), gameconfig::SOLID_TEXT_COLOR_OK, GetWidth() - 10, GetHeight() / 2 - 15, ALLEGRO_ALIGN_RIGHT, "ON");
	else
		al_draw_text(game_GetFont("default", 30), gameconfig::SOLID_TEXT_COLOR_ERROR, GetWidth() - 10, GetHeight() / 2 - 15, ALLEGRO_ALIGN_RIGHT, "OFF");
}

bool SimpleToggleTextButtonUIComponent::ClickLeftUp(int xRel, int yRel)
{
	isToggled = !isToggled;
	return true;
}

bool SimpleToggleTextButtonUIComponent::ClickLeftDown(int xRel, int yRel)
{
	return true;
}

bool SimpleToggleTextButtonUIComponent::ClickRightUp(int xRel, int yRel)
{
	return true;
}

bool SimpleToggleTextButtonUIComponent::ClickRightDown(int xRel, int yRel)
{
	isToggled = !isToggled;
	return true;
}

bool SimpleToggleTextButtonUIComponent::GetIsToggledOn() const
{
	return isToggled;
}

void SimpleToggleTextButtonUIComponent::SetIsToggledOn(bool on)
{
	isToggled = on;
}

SimpleToggleTextButtonUIComponent::SimpleToggleTextButtonUIComponent(int x, int y, int w, int h, ALLEGRO_COLOR bc, ALLEGRO_COLOR tc, std::string txt, bool isOn) : UIComponent(x, y, w, h), background_color{ bc }, text_color{ tc }, text{ txt }, isToggled{ isOn }
{}
