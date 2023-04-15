#pragma once
#include <allegro5/allegro5.h>

#include "UIComponent.h"
#include <vector>

class PlayerEntity;
extern PlayerEntity* GUI_GLOBAL_PLAYER_OBJECT;

class GUI
{
protected:
	GUI* activeSubGUI = nullptr;
	bool typing = false;
	std::vector<UIComponent*> UIcomponents;
	UIComponent* selectedComponent;
public:
	static PlayerEntity* GetPlayer();

	virtual void PreDrawThisGUI();
	virtual void PostDrawThisGUI();

	UIComponent* GetSelectedComponent();

	bool IsTyping() const;
	void ToggleTyping();

	virtual void DrawGUI();


	virtual bool ClickRightDown(int xRel, int yRel);
	virtual bool ClickLeftDown(int xRel, int yRel);
	virtual bool ClickRightUp(int xRel, int yRel);
	virtual bool ClickLeftUp(int xRel, int yRel);
	
	virtual bool KeyDown(ALLEGRO_KEYBOARD_EVENT& event);
	virtual bool KeyUp(ALLEGRO_KEYBOARD_EVENT& event);

	void SetActiveSubGUI(GUI* gui);

	virtual bool KeyChar(ALLEGRO_KEYBOARD_EVENT& event);

	virtual bool MouseButtonDown(ALLEGRO_MOUSE_EVENT& event);
	virtual bool MouseButtonUp(ALLEGRO_MOUSE_EVENT& event);
	virtual bool MouseButtonMove(ALLEGRO_MOUSE_EVENT& event);

	virtual bool HandleEvent(ALLEGRO_EVENT& event);
};

