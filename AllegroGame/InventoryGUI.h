#pragma once
#include "GUI.h"
#include "Item.h"

class InventoryGUI;

enum SLOT_DISPLAY_CONFIGURATION_TYPE { STORAGE, FUNCTION };

class SlotDisplayConfiguration
{
private:
    int itemID;
    int xpos;
    int ypos;
    int width;
    int height;
    bool (*callback)(Item*);
    SLOT_DISPLAY_CONFIGURATION_TYPE type;
public:

    SlotDisplayConfiguration(int s, int x, int y);
    SlotDisplayConfiguration(int s, int x, int y, int w, int h);

    SlotDisplayConfiguration(bool (*c)(Item*), int x, int y);
    SlotDisplayConfiguration(bool (*c)(Item*), int x, int y, int w, int h);

    bool contains(int x, int y) const;

    SLOT_DISPLAY_CONFIGURATION_TYPE getType() const;

    bool execute(Item* item) const;

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

    InventoryGUI();
    
public:

    virtual void DrawThisGUI() override;

    void AddSlotDisplayConfiguration(SlotDisplayConfiguration slot);

    virtual ~InventoryGUI() = default;
};

