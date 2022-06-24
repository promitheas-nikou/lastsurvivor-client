#pragma once
#include <allegro5/allegro5.h>

#include "UIComponent.h"
#include <vector>

class GUI
{
protected:
	GUI* activeSubGUI = nullptr;
	bool typing = false;
	std::vector<UIComponent*> UIcomponents;
public:
	virtual void PreDrawThisGUI() = 0;
	virtual void PostDrawThisGUI() = 0;

	bool IsTyping() const;
	void ToggleTyping();

	virtual void DrawGUI();


	virtual bool ClickRightDown(int xRel, int yRel);
	virtual bool ClickLeftDown(int xRel, int yRel);
	virtual bool ClickRightUp(int xRel, int yRel);
	virtual bool ClickLeftUp(int xRel, int yRel);
	
	virtual bool KeyDown(ALLEGRO_KEYBOARD_EVENT& event);
	virtual bool KeyUp(ALLEGRO_KEYBOARD_EVENT& event);

	virtual bool CharTyped(ALLEGRO_KEYBOARD_EVENT& event);

	virtual bool MouseButtonDown(ALLEGRO_MOUSE_EVENT& event);
	virtual bool MouseButtonUp(ALLEGRO_MOUSE_EVENT& event);
	virtual bool MouseButtonMove(ALLEGRO_MOUSE_EVENT& event);

	virtual bool HandleEvent(ALLEGRO_EVENT& event);
};

