#pragma once

#include "UIComponent.h"

class RectangularUIComponent:
	public virtual UIComponent
{
protected:

	RectangularUIComponent();

public:

	bool ContainsPoint(int x, int y) const final;

	virtual ~RectangularUIComponent() = default;

};

