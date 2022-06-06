#pragma once
#include "RectangularUIComponent.h"
#include "SimpleUIComponent.h"
#include "BitmapUIComponent.h"
#include <functional>
#include "Item.h"

class ItemInventorySlotUIComponent:
    public RectangularUIComponent,
    public SimpleUIComponent,
    public BitmapUIComponent
{
private:
    Item*& swapptr;
    Item*& itemptr;
protected:
	virtual bool CheckCanSwap() const = 0;
public:

    virtual void ClickRightDown(int xRel, int yRel) final;
    virtual void ClickLeftDown(int xRel, int yRel) final;
    virtual void Hover(int xRel, int yRel) final;
	
    ItemInventorySlotUIComponent(ALLEGRO_BITMAP* b, Item*& i, Item*& s);

    virtual void Draw() final;

    virtual ~ItemInventorySlotUIComponent() = default;
};

