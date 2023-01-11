#pragma once


#include "RectangularUIComponent.h"
#include "SimpleUIComponent.h"
#include "BitmapUIComponent.h"
#include "Item.h"

class SimpleItemInventoryViewStorageSlotUIComponent :
    public RectangularUIComponent,
    public SimpleUIComponent,
    public BitmapUIComponent
{
protected:

    Item*& itemptr;

public:

    virtual void Draw(int plane) final;

    virtual bool Hover(int x, int y) final;

    SimpleItemInventoryViewStorageSlotUIComponent(int x, int y, int w, int h, ALLEGRO_BITMAP* b, Item*& i);

    virtual ~SimpleItemInventoryViewStorageSlotUIComponent() = default;
};