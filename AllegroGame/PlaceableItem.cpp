#include "PlaceableItem.h"
#include "World.h"

PlaceableItem::PlaceableItem() : UsableItem()
{}

bool PlaceableItem::Use(float x, float y, PlayerEntity * p)
{
	World* w = p->GetContainingWorld();
	int X = std::floorf(x);
	int Y = std::floorf(y);
	if (w->GetTile(X, Y)->IsEmpty())
	{
		Tile* newTile = GetTile(w, X, Y, p->GetBuildingRotation());
		if (!newTile)
			return false;
		delete w->SetTile(newTile, X, Y);
		return true;
	}
	return false;
}
