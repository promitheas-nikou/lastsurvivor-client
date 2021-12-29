#pragma once

#include "ButtonUIComponent.h"
#include "SimpleUIComponent.h"

#pragma warning(disable : 4250)

class SimpleButtonUIComponent:
	public virtual ButtonUIComponent,
	public virtual SimpleUIComponent
{
public:
	SimpleButtonUIComponent(int x, int y, int w, int h, ALLEGRO_BITMAP* tex, void (*func)(void));

	using SimpleUIComponent::Draw;

	virtual void ClickRightDown(int xRel, int yRel) final;
	virtual void ClickLeftUp(int xRel, int yRel) final;
	virtual void ClickRightUp(int xRel, int yRel) final;
	virtual void Hover(int xRel, int yRel) final;
	virtual void KeyDown(int key) final;
	virtual void KeyUp(int key) final;

	virtual ~SimpleButtonUIComponent() = default;

};

