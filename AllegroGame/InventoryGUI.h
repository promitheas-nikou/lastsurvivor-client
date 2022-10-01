#pragma once
#include "GUI.h"
#include "Item.h"
#include <functional>

class InventoryGUI;


class InventoryGUI :
    public GUI
{
public:
    static ALLEGRO_BITMAP* INVENTORY_SLOT_GENERIC;
    static ALLEGRO_BITMAP* INVENTORY_SLOT_CALLBACK;
    static ALLEGRO_BITMAP* INVENTORY_SLOT_TRASH;
    static ALLEGRO_BITMAP* INVENTORY_SLOT_SHOVEL;
    static ALLEGRO_BITMAP* INVENTORY_SLOT_PICKAXE;
    static ALLEGRO_BITMAP* INVENTORY_SLOT_AXE;
    static ALLEGRO_BITMAP* INVENTORY_SLOT_MELEE;
    static ALLEGRO_BITMAP* INVENTORY_SLOT_RANGED;
    static ALLEGRO_BITMAP* INVENTORY_SLOT_CONSUMABLE;
    static ALLEGRO_BITMAP* INVENTORY_SLOT_USABLE;
    static ALLEGRO_BITMAP* INVENTORY_SLOT_PLACEABLE;

protected:

    Item* swapTemp;

    int xoffset = 0;
    int yoffset = 0;

    virtual void SwapItem(Item** slot);
    
public:

    enum StorageSlotType { GENERIC, VIEW, SHOVEL, PICKAXE, AXE, MELEE, RANGED, CONSUMABLE, PLACEABLE, FUEL, OUTPUT, USABLE };

    InventoryGUI();

    virtual void DrawGUI() override;

    virtual void PreDrawThisGUI() override;
    virtual void PostDrawThisGUI() override;

    void AddSlot(int x, int y, int w, int h, Item*& itemslot, StorageSlotType t);
    void AddDynamicSlot(int x, int y, int w, int h, std::function<Item** ()> itemslotfun, StorageSlotType t);

    void AddCallbackSlot(int x, int y, int w, int h, std::function<Item* (Item*)> cl, std::function<Item* (Item*)> cr);
    void AddTrashSlot(int x, int y, int w, int h);

    void SetOffset(int xoff, int yoff);

    static void Init();

    virtual bool HandleEvent(ALLEGRO_EVENT& event);

    virtual ~InventoryGUI() = default;
};

