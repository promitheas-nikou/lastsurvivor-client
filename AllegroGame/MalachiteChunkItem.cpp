#include "MalachiteChunkItem.h"
#include "ResourceLoader.h"

std::string MalachiteChunkItem::NAME;
std::string MalachiteChunkItem::DESCRIPTION;
ALLEGRO_BITMAP* MalachiteChunkItem::TEXTURE;
const std::string MalachiteChunkItem::ID = "items.malachite_chunk";

std::string MalachiteChunkItem::GetID() const
{
    return ID;
}

MalachiteChunkItem::MalachiteChunkItem(): Item(NAME, DESCRIPTION)
{}

Item* MalachiteChunkItem::Clone() const
{
	return new MalachiteChunkItem(*this);
}

void MalachiteChunkItem::Draw(int x, int y, int width, int height) const
{
	al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
	al_draw_textf(game_GetFont("default", 30), al_map_rgb(255, 0, 0), x + width - 40, y + height - 40, 0, "%d", GetAmount());
}

void MalachiteChunkItem::Init(nlohmann::json data)
{
	NAME = data[DATA_JSON_NAME_KEY];
	TEXTURE = game_GetTexture(data[DATA_JSON_TEXTURE_KEY]);
}
