#include "MagnetiteChunkItem.h"
#include "ResourceLoader.h"

std::string MagnetiteChunkItem::NAME;
std::string MagnetiteChunkItem::DESCRIPTION;
ALLEGRO_BITMAP* MagnetiteChunkItem::TEXTURE;
const std::string MagnetiteChunkItem::ID = "items.magnetite_chunk";

std::string MagnetiteChunkItem::GetID() const
{
    return ID;
}

MagnetiteChunkItem::MagnetiteChunkItem(): Item(NAME, DESCRIPTION)
{}

Item* MagnetiteChunkItem::Clone() const
{
	return new MagnetiteChunkItem(*this);
}

void MagnetiteChunkItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
	al_draw_textf(game_GetFont("default", 30), al_map_rgb(255, 0, 0), x + width - 40, y + height - 40, 0, "%d", GetAmount());
}

void MagnetiteChunkItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	DESCRIPTION = data[DATA_JSON_DESCRIPTION_KEY];
	TEXTURE = game_GetTexture(data[DATA_JSON_TEXTURE_KEY]);
}
