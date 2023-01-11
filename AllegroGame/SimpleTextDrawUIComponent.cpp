#include "SimpleTextDrawUIComponent.h"
#include "ResourceLoader.h"

SimpleTextDrawUIComponent::SimpleTextDrawUIComponent(int x, int y, int w, int h, std::string txt, int size, ALLEGRO_COLOR color) : UIComponent(x, y, w, h), text{ txt }, size{ size }, color{ color }
{
}

void SimpleTextDrawUIComponent::Draw()
{
	al_draw_multiline_text(loaded_fonts["default"][size], al_map_rgba(0, 0, 0, 255), 0, 0, GetWidth(), size, 0, text.c_str());
}
