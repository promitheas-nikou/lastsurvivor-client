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

ALLEGRO_BITMAP* StoneItem::GetTexture() const
{
	return TEXTURE;
}

void StoneItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
}
