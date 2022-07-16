#include "SimpleItemInventoryCallbackSlotUIComponent.h"

SimpleItemInventoryCallbackSlotUIComponent::SimpleItemInventoryCallbackSlotUIComponent(int x, int y, int w, int h, ALLEGRO_BITMAP* b, std::function<Item* (Item*)> r, std::function<Item* (Item*)> l, Item*& i) : UIComponent(x, y, w, h), BitmapUIComponent(b), rClickCallback{ r }, lClickCallback{ l }, itemptr{ i }
{
}

bool SimpleItemInventoryCallbackSlotUIComponent::ClickRightDown(int xRel, int yRel)
{
	itemptr = rClickCallback(itemptr);
	return true;
}

bool SimpleItemInventoryCallbackSlotUIComponent::ClickLeftDown(int xRel, int yRel)
{
	itemptr = lClickCallback(itemptr);
	return true;
}

bool SimpleItemInventoryCallbackSlotUIComponent::Hover(int xRel, int yRel)
{
	return true;
}

void SimpleItemInventoryCallbackSlotUIComponent::Draw(int plane)
{
	if(plane==1)
		BitmapUIComponent::Draw(plane);
}
