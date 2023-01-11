#include "SimpleItemInventoryViewStorageSlotUIComponent.h"

void SimpleItemInventoryViewStorageSlotUIComponent::Draw(int plane)
{
	if (plane == 1)
	{
		BitmapUIComponent::Draw(plane);
		if (itemptr != nullptr)
			itemptr->Draw(0, 0, GetWidth(), GetHeight());
	}
}

bool SimpleItemInventoryViewStorageSlotUIComponent::Hover(int x, int y)
{
	if (itemptr != nullptr)
		itemptr->DrawItemDetailsPane(0, 0);
	return true;
}

SimpleItemInventoryViewStorageSlotUIComponent::SimpleItemInventoryViewStorageSlotUIComponent(int x, int y, int w, int h, ALLEGRO_BITMAP* b, Item*& i) : UIComponent(x, y, w, h), BitmapUIComponent(b), itemptr{ i }
{}
