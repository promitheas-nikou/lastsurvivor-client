#include "MagnetiteChunkItem.h"
#include "ResourceLoader.h"

std::string MagnetiteChunkItem::NAME;
ALLEGRO_BITMAP* MagnetiteChunkItem::TEXTURE;
const std::string MagnetiteChunkItem::ID = "items.magnetite_chunk";

std::string MagnetiteChunkItem::GetID() const
{
    return ID;
}

MagnetiteChunkItem::MagnetiteChunkItem(): Item(NAME)
{}

Item* MagnetiteChunkItem::Clone() const
{
	return new MagnetiteChunkItem(*this);
}

void MagnetiteChunkItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
	al_draw_textf(loaded_fonts["default"][30], al_map_rgb(255, 0, 0), x + width - 40, y + height - 40, 0, "%d", GetAmount());
}

void MagnetiteChunkItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]];
}
