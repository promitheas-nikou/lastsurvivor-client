#include "ButtonUIComponent.h"

ButtonUIComponent::ButtonUIComponent(void(*func)(void)) : onPress{ func }
{}

void ButtonUIComponent::ClickLeftDown(int xRel, int yRel)
{
	onPress();
}
