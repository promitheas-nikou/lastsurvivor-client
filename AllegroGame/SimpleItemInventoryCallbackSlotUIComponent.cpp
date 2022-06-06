#include "SimpleItemInventoryCallbackSlotUIComponent.h"

SimpleItemInventoryCallbackSlotUIComponent::SimpleItemInventoryCallbackSlotUIComponent(int x, int y, int w, int h, ALLEGRO_BITMAP* b, std::function<Item* (Item*)> r, std::function<Item* (Item*)> l, Item*& i) : UIComponent(x, y, w, h), BitmapUIComponent(b), rClickCallback{ r }, lClickCallback{ l }, itemptr{ i }
{
}

void SimpleItemInventoryCallbackSlotUIComponent::ClickRightDown(int xRel, int yRel)
{
	itemptr = rClickCallback(itemptr);
}

void SimpleItemInventoryCallbackSlotUIComponent::ClickLeftDown(int xRel, int yRel)
{
	itemptr = lClickCallback(itemptr);
}

void SimpleItemInventoryCallbackSlotUIComponent::Hover(int xRel, int yRel)
{}

void SimpleItemInventoryCallbackSlotUIComponent::Draw()
{
	BitmapUIComponent::Draw();
}
