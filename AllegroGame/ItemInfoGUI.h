#pragma once
#include "GUI.h"
#include "Item.h"

class ItemInfoGUI :
    public GUI
{
private:
    const Item* item;
public:

    void SetTargetItem(const Item* i);

    virtual bool KeyDown(ALLEGRO_KEYBOARD_EVENT& event) final;

    virtual void PreDrawThisGUI() final;
    virtual void PostDrawThisGUI() final;

};

