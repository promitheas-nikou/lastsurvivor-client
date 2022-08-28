#pragma once
#include "ButtonUIComponent.h"
#include "SimpleUIComponent.h"


class SimpleTextButtonUIComponent :
    public ButtonUIComponent
{
private:
    ALLEGRO_COLOR background_color;
    ALLEGRO_COLOR text_color;
    std::string text;
public:
    virtual void Draw(int plane) final;


	virtual bool ClickLeftUp(int xRel, int yRel) final;
	virtual bool ClickRightUp(int xRel, int yRel) final;
	virtual bool ClickRightDown(int xRel, int yRel) final;
	virtual bool Hover(int xRel, int yRel) final;
	virtual bool KeyDown(ALLEGRO_KEYBOARD_EVENT& evt) final;
	virtual bool KeyUp(ALLEGRO_KEYBOARD_EVENT& evt) final;
	virtual bool KeyChar(ALLEGRO_KEYBOARD_EVENT& evt) final;

    SimpleTextButtonUIComponent(int x, int y, int w, int h, std::function<void(void)> cb, ALLEGRO_COLOR bc, ALLEGRO_COLOR tc, std::string txt);
};

