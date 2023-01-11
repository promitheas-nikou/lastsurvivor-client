#include "SimpleButtonUIComponent.h"

SimpleButtonUIComponent::SimpleButtonUIComponent(int x, int y, int w, int h, ALLEGRO_BITMAP* tex, std::function<void(void)> func) : UIComponent(x, y, w, h), ButtonUIComponent(func), BitmapUIComponent(tex)
{}

bool SimpleButtonUIComponent::ClickRightDown(int xRel, int yRel)
{
	return false;
}

bool SimpleButtonUIComponent::ClickLeftUp(int xRel, int yRel)
{
	return false;
}

bool SimpleButtonUIComponent::ClickRightUp(int xRel, int yRel)
{
	return false;
}

bool SimpleButtonUIComponent::Hover(int xRel, int yRel)
{
	return false;
}

bool SimpleButtonUIComponent::KeyDown(ALLEGRO_KEYBOARD_EVENT& evt)
{
	return false;
}

bool SimpleButtonUIComponent::KeyUp(ALLEGRO_KEYBOARD_EVENT& evt)
{
	return false;
}

bool SimpleButtonUIComponent::KeyChar(ALLEGRO_KEYBOARD_EVENT& evt)
{
	return false;
}
