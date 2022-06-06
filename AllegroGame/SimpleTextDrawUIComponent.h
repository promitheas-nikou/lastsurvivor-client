#pragma once
#include <string>
#include "PhantomUIComponent.h"
#include "UIComponent.h"
#include "SimpleUIComponent.h"
#include <allegro5/allegro_font.h>

class SimpleTextDrawUIComponent:
	public PhantomUIComponent,
	public SimpleUIComponent
{
private:
	std::string text;
	int size;
	ALLEGRO_COLOR color;
public:

	SimpleTextDrawUIComponent(int x, int y, int w, int h, std::string txt, int size, ALLEGRO_COLOR color);

	virtual void Draw() final;
	
};

