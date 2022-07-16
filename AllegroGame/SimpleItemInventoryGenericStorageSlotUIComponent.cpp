#include "SimpleItemInventoryGenericStorageSlotUIComponent.h"

bool SimpleItemInventoryGenericStorageSlotUIComponent::ClickRightDown(int xRel, int yRel)
{
    if (swapptr != nullptr)
    {
        if (swapptr->Equals(itemptr))
        {
            itemptr->AddAmount(1);
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

bool SimpleItemInventoryGenericStorageSlotUIComponent::ClickLeftDown(int xRel, int yRel)
{
    if (swapptr != nullptr && swapptr->Equals(itemptr))
    {
        itemptr->AddAmount(swapptr->GetAmount());
        delete swapptr;
        swapptr = nullptr;
    }
    else
        std::swap(swapptr, itemptr);
    return true;
}

bool SimpleItemInventoryGenericStorageSlotUIComponent::Hover(int xRel, int yRel)
{
    return true;
}

void SimpleItemInventoryGenericStorageSlotUIComponent::Draw(int plane)
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

SimpleItemInventoryGenericStorageSlotUIComponent::SimpleItemInventoryGenericStorageSlotUIComponent(int x, int y, int w, int h, ALLEGRO_BITMAP* b, Item*& i, Item*& s) : UIComponent(x, y, w, h), BitmapUIComponent(b), itemptr{ i }, swapptr{ s }
{}