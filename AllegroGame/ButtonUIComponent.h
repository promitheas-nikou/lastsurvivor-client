#pragma once

#include "RectangularUIComponent.h"
#include <functional>

class ButtonUIComponent:
	public virtual RectangularUIComponent
{
protected:

	std::function<void(void)> onPress;

	ButtonUIComponent(std::function<void(void)> func);

public:

	bool ClickLeftDown(int xRel, int yRel) final;

	virtual ~ButtonUIComponent() = default;

};

