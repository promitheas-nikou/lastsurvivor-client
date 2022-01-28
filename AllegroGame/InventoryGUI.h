#pragma once
#include "GUI.h"
#include "Item.h"

class InventoryGUI;

class SlotDisplayConfiguration
{
private:
    int itemID;
    int xpos;
    int ypos;
    int width;
    int height;
public:
    SlotDisplayConfiguration(int s, int x, int y);
    SlotDisplayConfiguration(int s, int x, int y, int w, int h);

    bool contains(int x, int y) const;

    friend InventoryGUI;
};

class InventoryGUI :
    public GUI
{
protected:
    std::vector<SlotDisplayConfiguration> slots;
    Item* swapTemp;

    virtual Item* GetItem(int itemID) = 0;
    virtual void SetItem(int itemID, Item* temp) = 0;

    virtual void SwapItem(int slotID);

    virtual void ClickLeftDown(int x, int y) override;

    virtual void DrawSlot(const SlotDisplayConfiguration& data);

    InventoryGUI() = default;
    
public:

    virtual void DrawThisGUI() override;

    void AddSlotDisplayConfiguration(SlotDisplayConfiguration slot);

    virtual ~InventoryGUI() = default;
};

