#pragma once
#include "GUI.h"
#include <allegro5/allegro5.h>

class PlayerEntity;

class DeathGUI:
	public GUI
{
private:
	ALLEGRO_BITMAP* TEXTURE;
public:
	DeathGUI(PlayerEntity* p);
	void DrawThisGUI() final;
};

