#pragma once
#include "UIComponent.h"
class SimpleUIComponent :
    public virtual UIComponent
{
public:

	SimpleUIComponent();

    void Draw() override;

	virtual void ClickRightDown(int xRel, int yRel) override;
	virtual void ClickLeftDown(int xRel, int yRel) override;
	virtual void ClickRightUp(int xRel, int yRel) override;
	virtual void ClickLeftUp(int xRel, int yRel) override;
	virtual void Hover(int xRel, int yRel) override;
	virtual void KeyDown(int key) override;
	virtual void KeyUp(int key) override;

    virtual ~SimpleUIComponent() = default;
};

