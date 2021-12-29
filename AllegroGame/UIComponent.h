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

	virtual void ClickRightDown(int xRel, int yRel) = 0;
	virtual void ClickLeftDown(int xRel, int yRel) = 0;
	virtual void ClickRightUp(int xRel, int yRel) = 0;
	virtual void ClickLeftUp(int xRel, int yRel) = 0;
	virtual void Hover(int xRel, int yRel) = 0;
	virtual void KeyDown(int key) = 0;
	virtual void KeyUp(int key) = 0;

	virtual ~UIComponent() = default;
};

