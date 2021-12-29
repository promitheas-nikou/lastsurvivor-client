#pragma once

#include "RectangularUIComponent.h"

class ButtonUIComponent:
	public virtual RectangularUIComponent
{
protected:

	void (*onPress)(void);

	ButtonUIComponent(void(*func)(void));

public:

	void ClickLeftDown(int xRel, int yRel) final;

	virtual ~ButtonUIComponent() = default;

};

