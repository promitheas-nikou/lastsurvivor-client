#include "ButtonUIComponent.h"

ButtonUIComponent::ButtonUIComponent(std::function<void(void)> func) : onPress{ func }
{}

bool ButtonUIComponent::ClickLeftDown(int xRel, int yRel)
{
	onPress();
	return true;
}
