#pragma once
#include "UIComponent.h"
#include <allegro5/allegro5.h>

class BitmapUIComponent:
	public virtual UIComponent
{
private:
	ALLEGRO_BITMAP* bitmap;
public:
	BitmapUIComponent(ALLEGRO_BITMAP* b);

	void Draw(int plane) override;

	virtual ~BitmapUIComponent() = default;
};

