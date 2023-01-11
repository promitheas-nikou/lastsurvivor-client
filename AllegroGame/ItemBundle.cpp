#include "ItemBundle.h"
#include "SimpleItemBundle.h"

ItemBundle* ItemBundle::CreateFromJSON(nlohmann::json data)
{
	SimpleItemBundle* b = new SimpleItemBundle();
	for (nlohmann::json item : data["items"])
		b->AddItem(MakeItemFromJSON(item));
	return b;
}

void ItemBundle::AddItemBundle(ItemBundle* bundle)
{
	if (bundle == nullptr)
		return;
	for (int i = 0; i < bundle->GetSize(); i++)
		AddItem(bundle->GetItem(i));
	delete bundle;
}
