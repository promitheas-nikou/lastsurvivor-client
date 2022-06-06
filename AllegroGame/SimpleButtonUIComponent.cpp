#include "SimpleButtonUIComponent.h"

SimpleButtonUIComponent::SimpleButtonUIComponent(int x, int y, int w, int h, ALLEGRO_BITMAP* tex, void(*func)(void)) : UIComponent(x, y, w, h), ButtonUIComponent(func), BitmapUIComponent(tex)
{}

void SimpleButtonUIComponent::ClickRightDown(int xRel, int yRel)
{
}

void SimpleButtonUIComponent::ClickLeftUp(int xRel, int yRel)
{}

void SimpleButtonUIComponent::ClickRightUp(int xRel, int yRel)
{}

void SimpleButtonUIComponent::Hover(int xRel, int yRel)
{
}

void SimpleButtonUIComponent::KeyDown(int key)
{
}

void SimpleButtonUIComponent::KeyUp(int key)
{
}
