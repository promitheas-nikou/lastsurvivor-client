#pragma once
#include <allegro5/allegro5.h>

#include "UIComponent.h"
#include <vector>

extern int mousex;
extern int mousey;

class PlayerEntity;
class GUI;
extern PlayerEntity* GUI_GLOBAL_PLAYER_OBJECT;
extern GUI* GUI_GLOBAL_PLAYER_INVENTORY_HOVER_GUI;

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

	virtual void OpenGUIHere(GUI* gui);
	virtual void OpenGUITop(GUI* gui);

	virtual bool ClickRightDown(int xRel, int yRel);
	virtual bool ClickLeftDown(int xRel, int yRel);
	virtual bool ClickRightUp(int xRel, int yRel);
	virtual bool ClickLeftUp(int xRel, int yRel);
	
	virtual bool KeyDown(ALLEGRO_KEYBOARD_EVENT& event);
	virtual bool KeyUp(ALLEGRO_KEYBOARD_EVENT& event);

	void SetActiveSubGUI(GUI* gui);
	bool HasActiveSubGUI() const;

	virtual bool KeyChar(ALLEGRO_KEYBOARD_EVENT& event);

	virtual bool MouseButtonDown(ALLEGRO_MOUSE_EVENT& event);
	virtual bool MouseButtonUp(ALLEGRO_MOUSE_EVENT& event);
	virtual bool MouseButtonMove(ALLEGRO_MOUSE_EVENT& event);

	virtual bool HandleEvent(ALLEGRO_EVENT& event);
};

