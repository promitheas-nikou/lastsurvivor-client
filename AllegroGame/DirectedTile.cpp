#include "DirectedTile.h"

DirectedTile::DirectedTile(World* w, int x, int y) : Tile(w, x, y), direction()
{}
DirectedTile::DirectedTile(World* w, int x, int y, Direction d) : Tile(w, x, y), direction{ d }
{}

Direction DirectedTile::GetDirection() const
{
	return direction;
}

void DirectedTile::SerializeToStream(std::ostream& file)
{
	Tile::SerializeToStream(file);
	uint8_t temp = direction.GetRawValue();
	file.write(reinterpret_cast<char*>(&temp), sizeof(uint8_t));
}

void DirectedTile::DeserializeFromStream(std::istream& file)
{
	Tile::DeserializeFromStream(file);
	uint8_t temp;
	file.read(reinterpret_cast<char*>(&temp), sizeof(uint8_t));
	direction = temp;
}
