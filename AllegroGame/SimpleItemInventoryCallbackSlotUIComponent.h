#pragma once
#include "RectangularUIComponent.h"
#include "SimpleUIComponent.h"
#include "BitmapUIComponent.h"
#include <functional>
#include "Item.h"

class SimpleItemInventoryCallbackSlotUIComponent :
    public RectangularUIComponent,
    public SimpleUIComponent,
    public BitmapUIComponent
{
private:
    std::function<Item* (Item*)> rClickCallback;
    std::function<Item* (Item*)> lClickCallback;
    Item*& itemptr;
public:

    SimpleItemInventoryCallbackSlotUIComponent(int x, int y, int w, int h, ALLEGRO_BITMAP* b, std::function<Item* (Item*)> r, std::function<Item* (Item*)> l, Item*& i);

    virtual bool ClickRightDown(int xRel, int yRel) final;
    virtual bool ClickLeftDown(int xRel, int yRel) final;
    virtual bool Hover(int xRel, int yRel) final;

    virtual void Draw() final;

    virtual ~SimpleItemInventoryCallbackSlotUIComponent() = default;
};

