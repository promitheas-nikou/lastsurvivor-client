#pragma once

#include <allegro5/allegro5.h>

class UIComponent
{
protected:

	int xpos;
	int ypos;
	int width;
	int height;

	UIComponent(int x, int y, int w, int h);

public:
	virtual bool ContainsPoint(int x, int y) const = 0;

	int GetXpos() const;
	int GetYpos() const;
	int GetWidth() const;
	int GetHeight() const;

	virtual void Draw(int plane) = 0;

	virtual bool ClickRightDown(int xRel, int yRel) = 0;
	virtual bool ClickLeftDown(int xRel, int yRel) = 0;
	virtual bool ClickRightUp(int xRel, int yRel) = 0;
	virtual bool ClickLeftUp(int xRel, int yRel) = 0;
	virtual bool Hover(int xRel, int yRel) = 0;
	virtual bool KeyDown(ALLEGRO_KEYBOARD_EVENT& evt) = 0;
	virtual bool KeyUp(ALLEGRO_KEYBOARD_EVENT& evt) = 0;
	virtual bool KeyChar(ALLEGRO_KEYBOARD_EVENT& evt) = 0;

	virtual ~UIComponent() = default;
};

