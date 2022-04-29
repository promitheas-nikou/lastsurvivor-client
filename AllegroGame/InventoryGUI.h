#pragma once
#include "GUI.h"
#include "Item.h"
#include <functional>

class InventoryGUI;

enum SLOT_DISPLAY_CONFIGURATION_TYPE { STORAGE, SHOVEL, PICKAXE, AXE, MELEE, RANGED, CONSUMABLE, PLACEABLE, FUNCTION };

class SlotDisplayConfiguration
{
private:
    Item** item_slot;
    int xpos;
    int ypos;
    int width;
    int height;
    std::function<Item* (Item*)> callback;
    SLOT_DISPLAY_CONFIGURATION_TYPE type;
public:

    SlotDisplayConfiguration(Item** s, int x, int y, SLOT_DISPLAY_CONFIGURATION_TYPE type = STORAGE);
    SlotDisplayConfiguration(Item** s, int x, int y, int w, int h, SLOT_DISPLAY_CONFIGURATION_TYPE type = STORAGE);

    SlotDisplayConfiguration(std::function<Item* (Item*)> callback, int x, int y);
    SlotDisplayConfiguration(std::function<Item* (Item*)> callback, int x, int y, int w, int h);

    bool contains(int x, int y) const;

    SLOT_DISPLAY_CONFIGURATION_TYPE getType() const;

    Item* execute(Item* item) const;

    friend InventoryGUI;
};

class InventoryGUI :
    public GUI
{
protected:
    static ALLEGRO_BITMAP* INVENTORY_SLOT;
    static ALLEGRO_BITMAP* INVENTORY_SLOT_CALLBACK;
    static ALLEGRO_BITMAP* INVENTORY_SLOT_SHOVEL;
    static ALLEGRO_BITMAP* INVENTORY_SLOT_PICKAXE;
    static ALLEGRO_BITMAP* INVENTORY_SLOT_AXE;
    static ALLEGRO_BITMAP* INVENTORY_SLOT_MELEE;
    static ALLEGRO_BITMAP* INVENTORY_SLOT_RANGED;
    static ALLEGRO_BITMAP* INVENTORY_SLOT_CONSUMABLE;
    static ALLEGRO_BITMAP* INVENTORY_SLOT_PLACEABLE;

    std::vector<SlotDisplayConfiguration> slots;
    Item* swapTemp;

    virtual void SwapItem(Item** slot);

    virtual void ClickLeftDown(int x, int y) override;

    virtual void DrawSlot(const SlotDisplayConfiguration& data, bool selected = false);
    
public:

    InventoryGUI();

    virtual void DrawThisGUI() override;

    void AddSlotDisplayConfiguration(SlotDisplayConfiguration slot);

    static void Init();

    virtual ~InventoryGUI() = default;
};

