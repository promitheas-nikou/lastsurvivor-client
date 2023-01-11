#include "SimpleDynamicItemInventoryOutputStorageSlotUIComponent.h"

bool SimpleDynamicItemInventoryOutputStorageSlotUIComponent::ClickRightDown(int xRel, int yRel)
{
    Item*& itemptr = *(itemptrfunc());
    if (itemptr == nullptr)
        return true;

    if (swapptr == nullptr) {
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

    if (swapptr->Equals(itemptr))
    {
        int newAmount = (itemptr->GetAmount() + 1) / 2;
        itemptr->RemoveAmount(newAmount - swapptr->AddAmount(newAmount));
        if (itemptr->GetAmount() == 0)
        {
            delete itemptr;
            itemptr = nullptr;
        }
    }

    return true;
}

bool SimpleDynamicItemInventoryOutputStorageSlotUIComponent::ClickLeftDown(int xRel, int yRel)
{
    Item*& itemptr = *(itemptrfunc());
    if (itemptr == nullptr)
        return true;

    if (swapptr == nullptr)
    {
        std::swap(swapptr, itemptr);
        return true;
    }
    if (swapptr->Equals(itemptr))
    {
        itemptr->SetAmount(swapptr->AddAmount(itemptr->GetAmount()));
        if (itemptr->GetAmount() == 0)
        {
            delete itemptr;
            itemptr = nullptr;
        }
    }
    return true;
}

bool SimpleDynamicItemInventoryOutputStorageSlotUIComponent::Hover(int xRel, int yRel)
{
    return true;
}

void SimpleDynamicItemInventoryOutputStorageSlotUIComponent::Draw(int plane)
{
    Item*& itemptr = *(itemptrfunc());
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

SimpleDynamicItemInventoryOutputStorageSlotUIComponent::SimpleDynamicItemInventoryOutputStorageSlotUIComponent(int x, int y, int w, int h, ALLEGRO_BITMAP* b, std::function<Item**()> i, Item*& s) : UIComponent(x, y, w, h), BitmapUIComponent(b), itemptrfunc{ i }, swapptr{ s }
{}
