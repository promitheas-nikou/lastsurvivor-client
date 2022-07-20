#pragma once

#include "ButtonUIComponent.h"
#include "BitmapUIComponent.h"
#include <functional>

#pragma warning(disable : 4250)

class SimpleButtonUIComponent:
	public ButtonUIComponent,
	public BitmapUIComponent
{
public:
	SimpleButtonUIComponent(int x, int y, int w, int h, ALLEGRO_BITMAP* tex, std::function<void(void)> func);

	using BitmapUIComponent::Draw;

	virtual bool ClickRightDown(int xRel, int yRel) final;
	virtual bool ClickLeftUp(int xRel, int yRel) final;
	virtual bool ClickRightUp(int xRel, int yRel) final;
	virtual bool Hover(int xRel, int yRel) final;
	virtual bool KeyDown(int key) final;
	virtual bool KeyUp(int key) final;

	virtual ~SimpleButtonUIComponent() = default;

};

