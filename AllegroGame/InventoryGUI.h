#pragma once
#include "GUI.h"
#include "Item.h"
#include <functional>

class InventoryGUI;


class InventoryGUI :
    public GUI
{
protected:
    static ALLEGRO_BITMAP* INVENTORY_SLOT_GENERIC;
    static ALLEGRO_BITMAP* INVENTORY_SLOT_CALLBACK;
    static ALLEGRO_BITMAP* INVENTORY_SLOT_SHOVEL;
    static ALLEGRO_BITMAP* INVENTORY_SLOT_PICKAXE;
    static ALLEGRO_BITMAP* INVENTORY_SLOT_AXE;
    static ALLEGRO_BITMAP* INVENTORY_SLOT_MELEE;
    static ALLEGRO_BITMAP* INVENTORY_SLOT_RANGED;
    static ALLEGRO_BITMAP* INVENTORY_SLOT_CONSUMABLE;
    static ALLEGRO_BITMAP* INVENTORY_SLOT_PLACEABLE;

    Item* swapTemp;

    virtual void SwapItem(Item** slot);
    
public:

    enum StorageSlotType { GENERIC, SHOVEL, PICKAXE, AXE, MELEE, RANGED, CONSUMABLE, PLACEABLE };

    InventoryGUI();

    virtual void PreDrawThisGUI() override;
    virtual void PostDrawThisGUI() override;

    void AddSlot(int x, int y, int w, int h, Item*& itemslot, StorageSlotType t);

    void AddCallbackSlot(int x, int y, int w, int h, std::function<Item*(Item*)> c);

    static void Init();

    virtual ~InventoryGUI() = default;
};

