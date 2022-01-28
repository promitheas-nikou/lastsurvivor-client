#include "DirtItem.h"
#include "ResourceLoader.h"

std::string DirtItem::NAME;
ALLEGRO_BITMAP* DirtItem::TEXTURE;

int DirtItem::GetID() const
{
	return ID;
}

DirtItem::DirtItem() : Item(NAME)
{}

ALLEGRO_BITMAP* DirtItem::GetTexture() const
{
	return TEXTURE;
}

void DirtItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
}
