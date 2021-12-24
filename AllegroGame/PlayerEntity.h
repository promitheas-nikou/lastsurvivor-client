#pragma once
#include "Entity.h"
#include "GUI.h"

static enum GUI_STATE {WORLD};

class PlayerEntity :
    public Entity,
	public GUI
{
private:
	GUI_STATE guistate;
	char keys_pressed;
public:
	void DrawThisGUI() final;
	void Draw() final;

	void KeyDown(ALLEGRO_KEYBOARD_EVENT &event) final;
	void KeyUp(ALLEGRO_KEYBOARD_EVENT &event) final;

	void MouseButtonDown(ALLEGRO_MOUSE_EVENT &event) final;
	void MouseButtonUp(ALLEGRO_MOUSE_EVENT &event) final;
	void MouseButtonMove(ALLEGRO_MOUSE_EVENT &event) final;

	void Tick() final;

	PlayerEntity(World* world);

	friend WorldChunk;
	friend World;
	friend int main();
};

