#pragma once
#include <functional>
#include "RectangularUIComponent.h"
#include "SimpleUIComponent.h"
#include "BitmapUIComponent.h"
#include "Item.h"

class SimpleDynamicItemInventoryGenericStorageSlotUIComponent :
    public RectangularUIComponent,
    public SimpleUIComponent,
    public BitmapUIComponent
{
protected:

    Item*& swapptr;
    std::function<Item** ()> itemptrfunc;
    int mouseXpos, mouseYpos;

public:

    virtual bool ClickRightDown(int xRel, int yRel) final;
    virtual bool ClickLeftDown(int xRel, int yRel) final;
    virtual bool Hover(int xRel, int yRel) final;

    virtual void Draw(int plane) final;

    SimpleDynamicItemInventoryGenericStorageSlotUIComponent(int x, int y, int w, int h, ALLEGRO_BITMAP* b, std::function<Item** ()> i, Item*& s);

    virtual ~SimpleDynamicItemInventoryGenericStorageSlotUIComponent() = default;
};

