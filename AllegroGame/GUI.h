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
	virtual void DrawThisGUI() = 0;

	bool IsTyping() const;
	void ToggleTyping();

	virtual void DrawGUI();


	virtual void ClickRightDown(int xRel, int yRel);
	virtual void ClickLeftDown(int xRel, int yRel);
	virtual void ClickRightUp(int xRel, int yRel);
	virtual void ClickLeftUp(int xRel, int yRel);
	
	virtual void KeyDown(ALLEGRO_KEYBOARD_EVENT& event);
	virtual void KeyUp(ALLEGRO_KEYBOARD_EVENT& event);

	virtual void CharTyped(ALLEGRO_KEYBOARD_EVENT& event);

	virtual void MouseButtonDown(ALLEGRO_MOUSE_EVENT& event);
	virtual void MouseButtonUp(ALLEGRO_MOUSE_EVENT& event);
	virtual void MouseButtonMove(ALLEGRO_MOUSE_EVENT& event);

	virtual void HandleEvent(ALLEGRO_EVENT& event);
};

