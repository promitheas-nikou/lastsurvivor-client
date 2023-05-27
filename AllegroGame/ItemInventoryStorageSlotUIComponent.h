#pragma once
#include "RectangularUIComponent.h"
#include "SimpleUIComponent.h"
#include "BitmapUIComponent.h"
#include "Item.h"


class ItemInventoryStorageSlotUIComponent :
    public RectangularUIComponent,
    public SimpleUIComponent,
    public BitmapUIComponent
{
protected:

    Item*& itemptr;
    int mouseXpos, mouseYpos;

public:

    virtual bool ClickRightDown(int xRel, int yRel) override;
    virtual bool ClickLeftDown(int xRel, int yRel) override;
    virtual bool Hover(int xRel, int yRel) override;
    virtual bool KeyDown(ALLEGRO_KEYBOARD_EVENT& e) override;

    virtual void Draw(int plane) override;

    virtual bool ItemCheckPredicate() const = 0;

    ItemInventoryStorageSlotUIComponent(int x, int y, int w, int h, ALLEGRO_BITMAP* b, Item*& i, Item*& s);

    virtual ~ItemInventoryStorageSlotUIComponent() = default;
};

