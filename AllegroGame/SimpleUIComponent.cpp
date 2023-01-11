#include "SimpleUIComponent.h"
#include <allegro5/allegro_primitives.h>
#include <cstdio>

SimpleUIComponent::SimpleUIComponent()
{}

void SimpleUIComponent::Draw(int plane)
{
}

bool SimpleUIComponent::ClickRightDown(int xRel, int yRel)
{
	return false;
}

bool SimpleUIComponent::ClickLeftDown(int xRel, int yRel)
{
	return false;
}

bool SimpleUIComponent::ClickRightUp(int xRel, int yRel)
{
	return false;
}

bool SimpleUIComponent::ClickLeftUp(int xRel, int yRel)
{
	return false;
}

bool SimpleUIComponent::Hover(int xRel, int yRel)
{
	return false;
}

bool SimpleUIComponent::KeyDown(ALLEGRO_KEYBOARD_EVENT& evt)
{
	return false;
}

bool SimpleUIComponent::KeyUp(ALLEGRO_KEYBOARD_EVENT& evt)
{
	return false;
}

bool SimpleUIComponent::KeyChar(ALLEGRO_KEYBOARD_EVENT& evt)
{
	return false;
}

