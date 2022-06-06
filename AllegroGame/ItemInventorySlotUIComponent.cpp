#include "ItemInventorySlotUIComponent.h"

void ItemInventorySlotUIComponent::ClickRightDown(int xRel, int yRel)
{
    ItemInventorySlotUIComponent::ClickLeftDown(xRel, yRel);
}

void ItemInventorySlotUIComponent::ClickLeftDown(int xRel, int yRel)
{
    if (CheckCanSwap())
        std::swap(swapptr, itemptr);
}

void ItemInventorySlotUIComponent::Hover(int xRel, int yRel)
{
}

ItemInventorySlotUIComponent::ItemInventorySlotUIComponent(ALLEGRO_BITMAP* b, Item*& i, Item*& s) : BitmapUIComponent(b), itemptr{ i }, swapptr{ s }
{}

void ItemInventorySlotUIComponent::Draw()
{
    BitmapUIComponent::Draw();
    if (itemptr != nullptr)
            itemptr->Draw(0, 0, GetWidth(), GetHeight());

}
