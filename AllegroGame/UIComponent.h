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

	virtual void Draw() = 0;

	virtual bool ClickRightDown(int xRel, int yRel) = 0;
	virtual bool ClickLeftDown(int xRel, int yRel) = 0;
	virtual bool ClickRightUp(int xRel, int yRel) = 0;
	virtual bool ClickLeftUp(int xRel, int yRel) = 0;
	virtual bool Hover(int xRel, int yRel) = 0;
	virtual bool KeyDown(int key) = 0;
	virtual bool KeyUp(int key) = 0;

	virtual ~UIComponent() = default;
};

