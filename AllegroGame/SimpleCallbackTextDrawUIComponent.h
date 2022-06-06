#pragma once
#include <string>
#include "PhantomUIComponent.h"
#include "UIComponent.h"
#include "SimpleUIComponent.h"
#include <allegro5/allegro_font.h>
#include <functional>

class SimpleCallbackTextDrawUIComponent:
	public PhantomUIComponent,
	public SimpleUIComponent
{
protected:
	std::function<std::string()> textCallback;
	std::function<int()> sizeCallback;
	std::function<ALLEGRO_COLOR()> colorCallback;
public:
	virtual ~SimpleCallbackTextDrawUIComponent() = default;

	virtual void Draw() final;
};

