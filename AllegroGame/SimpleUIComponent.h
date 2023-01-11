#pragma once
#include "UIComponent.h"
class SimpleUIComponent :
    public virtual UIComponent
{
public:

	SimpleUIComponent();

    void Draw(int plane) override;

	virtual bool ClickRightDown(int xRel, int yRel) override;
	virtual bool ClickLeftDown(int xRel, int yRel) override;
	virtual bool ClickRightUp(int xRel, int yRel) override;
	virtual bool ClickLeftUp(int xRel, int yRel) override;
	virtual bool Hover(int xRel, int yRel) override;
	virtual bool KeyDown(ALLEGRO_KEYBOARD_EVENT& evt) override;
	virtual bool KeyUp(ALLEGRO_KEYBOARD_EVENT& evt) override;
	virtual bool KeyChar(ALLEGRO_KEYBOARD_EVENT& evt) override;

    virtual ~SimpleUIComponent() = default;
};

