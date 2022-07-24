#include "SimpleItemInventoryPlaceableStorageSlotUIComponent.h"
#include "PlaceableItem.h"

bool SimpleItemInventoryPlaceableStorageSlotUIComponent::ClickRightDown(int xRel, int yRel)
{
    if (swapptr != nullptr)
    {
        if (dynamic_cast<PlaceableItem*>(swapptr) == nullptr)
            return true;
        if (swapptr->Equals(itemptr))
        {
            if(itemptr->AddAmount(1))
                return true;
            swapptr->RemoveAmount(1);
            if (swapptr->GetAmount() == 0)
            {
                delete swapptr;
                swapptr = nullptr;
            }
        }
        else if(itemptr==nullptr)
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
    }
    else
    {
        if (itemptr == nullptr)
            return true;
        int newAmount = (itemptr->GetAmount()+1) / 2;
        swapptr = itemptr->Clone();
        swapptr->SetAmount(newAmount);
        itemptr->RemoveAmount(newAmount);
        if (itemptr->GetAmount() == 0)
        {
            delete itemptr;
            itemptr = nullptr;
        }
    }
    return true;
}

bool SimpleItemInventoryPlaceableStorageSlotUIComponent::ClickLeftDown(int xRel, int yRel)
{
    if (swapptr == nullptr)
    {
        std::swap(itemptr, swapptr);
        return true;
    }
    if (dynamic_cast<PlaceableItem*>(swapptr) == nullptr)
        return true;
    if (itemptr == nullptr) {
        std::swap(itemptr, swapptr);
        return true;
    }
    if (swapptr->Equals(itemptr))
    {
        int a = swapptr->GetAmount();
        swapptr->RemoveAmount(a-itemptr->AddAmount(a));
        if (swapptr->GetAmount() == 0)
        {
            delete swapptr;
            swapptr = nullptr;
        }
    }
    else
    {
        std::swap(itemptr, swapptr);
    }
    return true;
}

bool SimpleItemInventoryPlaceableStorageSlotUIComponent::Hover(int xRel, int yRel)
{
    return true;
}

void SimpleItemInventoryPlaceableStorageSlotUIComponent::Draw(int plane)
{
    switch (plane)
    {
    case 1:
        BitmapUIComponent::Draw(1);
        if (itemptr != nullptr)
        {
            itemptr->Draw(0, 0, GetWidth(), GetHeight());
        }
        break;
    case 2:
        if (itemptr != nullptr)
        {
            int x, y;
            al_get_mouse_cursor_position(&x, &y);
            if (0 <= x - GetXpos() && x - GetXpos() < GetWidth() && 0 <= y - GetYpos() && y - GetYpos() < GetHeight())
                itemptr->DrawItemDetailsPane(x - GetXpos(), y - GetYpos());
        }
        break;
    }
}

SimpleItemInventoryPlaceableStorageSlotUIComponent::SimpleItemInventoryPlaceableStorageSlotUIComponent(int x, int y, int w, int h, ALLEGRO_BITMAP* b, Item*& i, Item*& s) : UIComponent(x, y, w, h), BitmapUIComponent(b), itemptr{ i }, swapptr{ s }
{}