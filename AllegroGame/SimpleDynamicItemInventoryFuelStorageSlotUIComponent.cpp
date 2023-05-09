#include "SimpleDynamicItemInventoryFuelStorageSlotUIComponent.h"
#include "FuelItem.h"
#include "GUI.h"
#include "PlayerEntity.h"

bool SimpleDynamicItemInventoryFuelStorageSlotUIComponent::ClickRightDown(int xRel, int yRel)
{
    Item*& itemptr = *(itemptrfunc());
    Item*& swapptr = GUI_GLOBAL_PLAYER_OBJECT->GetStashedItem();

    if (swapptr == nullptr)
    {
        if (itemptr == nullptr)
            return true;
        int newAmount = (itemptr->GetAmount() + 1) / 2;
        swapptr = itemptr->Clone();
        swapptr->SetAmount(newAmount);
        itemptr->RemoveAmount(newAmount);
        if (itemptr->GetAmount() == 0)
        {
            delete itemptr;
            itemptr = nullptr;
        }
        return true;
    }
    if (dynamic_cast<FuelItem*>(swapptr) == nullptr)
        return true;
    if (swapptr->Equals(itemptr))
    {
        if (itemptr->AddAmount(1))
            return true;
        swapptr->RemoveAmount(1);
        if (swapptr->GetAmount() == 0)
        {
            delete swapptr;
            swapptr = nullptr;
        }
    }
    else if (itemptr == nullptr)
    {
        itemptr = swapptr->Clone();
        itemptr->SetAmount(1);
        swapptr->RemoveAmount(1);
        if (swapptr->GetAmount() == 0)
        {
            delete swapptr;
            swapptr = nullptr;
        }
    }
    return true;
}

bool SimpleDynamicItemInventoryFuelStorageSlotUIComponent::ClickLeftDown(int xRel, int yRel)
{
    Item*& itemptr = *(itemptrfunc());
    Item*& swapptr = GUI_GLOBAL_PLAYER_OBJECT->GetStashedItem();

    if (swapptr == nullptr)
    {
        std::swap(itemptr, swapptr);
        return true;
    }
    if (dynamic_cast<FuelItem*>(swapptr) == nullptr)
        return true;
    if (itemptr == nullptr)
    {
        std::swap(itemptr, swapptr);
        return true;
    }
    if (swapptr->GetMaxStackSize() == 1 || itemptr->GetMaxStackSize() == 1)
    {
        std::swap(itemptr, swapptr);
        return true;
    }
    if (swapptr->Equals(itemptr))
    {
        swapptr->SetAmount(itemptr->AddAmount(swapptr->GetAmount()));
        if (swapptr->GetAmount() == 0)
        {
            delete swapptr;
            swapptr = nullptr;
        }
    }
    else
        std::swap(swapptr, itemptr);
    return true;
}

bool SimpleDynamicItemInventoryFuelStorageSlotUIComponent::Hover(int xRel, int yRel)
{
    return true;
}

void SimpleDynamicItemInventoryFuelStorageSlotUIComponent::Draw(int plane)
{
    Item*& itemptr = *(itemptrfunc());

    switch (plane)
    {
    case 1:
        BitmapUIComponent::Draw(1);
        printf("BEGIN1 %p\n", itemptr);
        if (itemptr != nullptr)
        {
            printf("END1 %p\n", itemptr);
            itemptr->Draw(0, 0, GetWidth(), GetHeight());   
        }
        break;
    case 2:
        printf("BEGIN2 %p\n", itemptr);
        if (itemptr != nullptr)
        {
            if (0 <= mousex - GetXpos() && mousex - GetXpos() < GetWidth() && 0 <= mousey - GetYpos() && mousey - GetYpos() < GetHeight())
                printf("END2 %p\n", itemptr);
                itemptr->DrawItemDetailsPane(mousex - GetXpos(), mousey - GetYpos());
        }
        break;
    }
}

SimpleDynamicItemInventoryFuelStorageSlotUIComponent::SimpleDynamicItemInventoryFuelStorageSlotUIComponent(int x, int y, int w, int h, ALLEGRO_BITMAP* b, std::function<Item** ()> i, Item*& s) : UIComponent(x, y, w, h), BitmapUIComponent(b), itemptrfunc{ i }
{}