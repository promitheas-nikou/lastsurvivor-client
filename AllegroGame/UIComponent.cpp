#include "UIComponent.h"

UIComponent::UIComponent(int x, int y, int w, int h): xpos{x}, ypos{y}, width{w}, height{h}
{}

int UIComponent::GetXpos() const
{
	return xpos;
}

int UIComponent::GetYpos() const
{
	return ypos;
}

int UIComponent::GetWidth() const
{
	return width;
}

int UIComponent::GetHeight() const
{
	return height;
}
