#pragma once
#include <allegro5/allegro5.h>

class GUI
{
protected:
	GUI* activeSubGUI;
public:
	virtual void DrawThisGUI() = 0;

	virtual void DrawGUI();

	virtual void KeyDown(ALLEGRO_KEYBOARD_EVENT& event) = 0;
	virtual void KeyUp(ALLEGRO_KEYBOARD_EVENT& event) = 0;
	
	virtual void MouseButtonDown(ALLEGRO_MOUSE_EVENT& event) = 0;
	virtual void MouseButtonUp(ALLEGRO_MOUSE_EVENT& event) = 0;
	virtual void MouseButtonMove(ALLEGRO_MOUSE_EVENT& event) = 0;

	virtual void HandleEvent(ALLEGRO_EVENT& event);
};

