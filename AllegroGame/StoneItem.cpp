#include "StoneItem.h"
#include "ResourceLoader.h"

std::string StoneItem::NAME;
ALLEGRO_BITMAP* StoneItem::TEXTURE;

int StoneItem::GetID() const
{
    return ID;
}

StoneItem::StoneItem(): Item(NAME)
{}

void StoneItem::Init(nlohmann::json data)
{
	NAME = data["name"];
	TEXTURE = loaded_bitmaps[data["texture_id"]];
}
