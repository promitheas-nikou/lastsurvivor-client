#pragma once
#include <string>
#include "SimpleUIComponent.h"
#include "RectangularUIComponent.h"

class SimpleToggleTextButtonUIComponent:
	public SimpleUIComponent,
	public RectangularUIComponent
{
private:
	bool isToggled;
	std::string text;
	ALLEGRO_COLOR background_color;
	ALLEGRO_COLOR text_color;
public:
	virtual void Draw(int plane) final;


	virtual bool ClickLeftUp(int xRel, int yRel) final;
	virtual bool ClickLeftDown(int xRel, int yRel) final;
	virtual bool ClickRightUp(int xRel, int yRel) final;
	virtual bool ClickRightDown(int xRel, int yRel) final;

	bool GetIsToggledOn() const;
	void SetIsToggledOn(bool on);

	SimpleToggleTextButtonUIComponent(int x, int y, int w, int h, ALLEGRO_COLOR bc, ALLEGRO_COLOR tc, std::string txt, bool isOn = false);
};

