#include "SimpleItemInventoryViewStorageSlotUIComponent.h"

void SimpleItemInventoryViewStorageSlotUIComponent::Draw()
{
	BitmapUIComponent::Draw();
	if (itemptr != nullptr)
		itemptr->Draw(0, 0, GetWidth(), GetHeight());
}

SimpleItemInventoryViewStorageSlotUIComponent::SimpleItemInventoryViewStorageSlotUIComponent(int x, int y, int w, int h, ALLEGRO_BITMAP* b, Item*& i) : UIComponent(x, y, w, h), BitmapUIComponent(b), itemptr{ i }
{}
