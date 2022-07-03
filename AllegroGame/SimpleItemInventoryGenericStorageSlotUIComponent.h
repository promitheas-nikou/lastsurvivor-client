#pragma once


#include "RectangularUIComponent.h"
#include "SimpleUIComponent.h"
#include "BitmapUIComponent.h"
#include "Item.h"

class SimpleItemInventoryGenericStorageSlotUIComponent :
    public RectangularUIComponent,
    public SimpleUIComponent,
    public BitmapUIComponent
{
protected:

    Item*& swapptr;
    Item*& itemptr;

public:

    virtual bool ClickRightDown(int xRel, int yRel) final;
    virtual bool ClickLeftDown(int xRel, int yRel) final;
    virtual bool Hover(int xRel, int yRel) final;

    virtual void Draw() final;

    SimpleItemInventoryGenericStorageSlotUIComponent(int x, int y, int w, int h, ALLEGRO_BITMAP* b, Item*& i, Item*& s);

    virtual ~SimpleItemInventoryGenericStorageSlotUIComponent() = default;
};

