#include "SimpleUIComponent.h"
#include <allegro5/allegro_primitives.h>
#include <cstdio>

SimpleUIComponent::SimpleUIComponent()
{}

void SimpleUIComponent::Draw()
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

bool SimpleUIComponent::KeyDown(int key)
{
	return false;
}

bool SimpleUIComponent::KeyUp(int key)
{
	return false;
}

