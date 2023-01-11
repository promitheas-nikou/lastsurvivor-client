#include "HematiteChunkItem.h"
#include "ResourceLoader.h"

std::string HematiteChunkItem::NAME;
std::string HematiteChunkItem::DESCRIPTION;
ALLEGRO_BITMAP* HematiteChunkItem::TEXTURE;
const std::string HematiteChunkItem::ID = "items.hematite_chunk";

std::string HematiteChunkItem::GetID() const
{
    return ID;
}

HematiteChunkItem::HematiteChunkItem(): Item(NAME, DESCRIPTION)
{}

Item* HematiteChunkItem::Clone() const
{
	return new HematiteChunkItem(*this);
}

void HematiteChunkItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
	al_draw_textf(loaded_fonts["default"][30], al_map_rgb(255, 0, 0), x + width - 40, y + height - 40, 0, "%d", GetAmount());
}

void HematiteChunkItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	DESCRIPTION = data[DATA_JSON_DESCRIPTION_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
}
