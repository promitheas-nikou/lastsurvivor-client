#include "GlassSlabItem.h"
#include "ResourceLoader.h"

std::string GlassSlabItem::NAME;
std::string GlassSlabItem::DESCRIPTION;
ALLEGRO_BITMAP* GlassSlabItem::TEXTURE;
const std::string GlassSlabItem::ID = "items.glass_slab";

std::string GlassSlabItem::GetID() const
{
	return ID;
}

GlassSlabItem::GlassSlabItem(): Item(NAME, DESCRIPTION)
{}

Item* GlassSlabItem::Clone() const
{
	return new GlassSlabItem(*this);
}

void GlassSlabItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
	al_draw_textf(game_GetFont("default", 30), al_map_rgb(255, 0, 0), x + width - 40, y + height - 40, 0, "%d", GetAmount());
}

void GlassSlabItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	DESCRIPTION = data[DATA_JSON_DESCRIPTION_KEY];
	TEXTURE = game_GetTexture(data[DATA_JSON_TEXTURE_KEY]);
}

