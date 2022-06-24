#include "ItemInventorySlotUIComponent.h"

bool ItemInventorySlotUIComponent::ClickRightDown(int xRel, int yRel)
{
    return ItemInventorySlotUIComponent::ClickLeftDown(xRel, yRel);
}

bool ItemInventorySlotUIComponent::ClickLeftDown(int xRel, int yRel)
{
    if (CheckCanSwap())
        std::swap(swapptr, itemptr);
    return true;
}

bool ItemInventorySlotUIComponent::Hover(int xRel, int yRel)
{
    return true;
}

ItemInventorySlotUIComponent::ItemInventorySlotUIComponent(ALLEGRO_BITMAP* b, Item*& i, Item*& s) : BitmapUIComponent(b), itemptr{ i }, swapptr{ s }
{}

void ItemInventorySlotUIComponent::Draw()
{
    BitmapUIComponent::Draw();
    if (itemptr != nullptr)
            itemptr->Draw(0, 0, GetWidth(), GetHeight());

}
