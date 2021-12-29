#include "RectangularUIComponent.h"

RectangularUIComponent::RectangularUIComponent()
{}

bool RectangularUIComponent::ContainsPoint(int x, int y) const
{
	int xdif = x - xpos;
	int ydif = y - ypos;
	return (xdif >= 0) && (xdif <= width) && (ydif >= 0) && (ydif <= height);
}
