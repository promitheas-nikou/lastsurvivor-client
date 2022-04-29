#include "ConnectingTile.h"
#include "World.h"

char ConnectingTile::GetConnectionsChar() const
{
    return connections;
}

void ConnectingTile::SetHasNorthConnection(bool c)
{
    if (c)
        connections |= NORTH_MASK;
    else
        connections &= ~NORTH_MASK;
}

void ConnectingTile::SetHasEastConnection(bool c)
{
    if (c)
        connections |= EAST_MASK;
    else
        connections &= ~EAST_MASK;
}

void ConnectingTile::SetHasSouthConnection(bool c)
{
    if (c)
        connections |= SOUTH_MASK;
    else
        connections &= ~SOUTH_MASK;
}

void ConnectingTile::SetHasWestConnection(bool c)
{
    if (c)
        connections |= WEST_MASK;
    else
        connections &= ~WEST_MASK;
}

bool ConnectingTile::HasNorthConnection() const
{
    return connections & NORTH_MASK;
}

bool ConnectingTile::HasEastConnection() const
{
    return connections & EAST_MASK;
}

bool ConnectingTile::HasSouthConnection() const
{
    return connections & SOUTH_MASK;
}

bool ConnectingTile::HasWestConnection() const
{
    return connections & WEST_MASK;
}

ConnectingTile::ConnectingTile(World* w, int x, int y, char connections): Tile(w, x, y), connections{ connections }
{}

bool ConnectingTile::ShouldConnect(Tile* tile) const
{
    return dynamic_cast<ConnectingTile*>(tile)!=nullptr;
}

void ConnectingTile::TileUpdate()
{
    Tile::TileUpdate();
    SetHasNorthConnection(this->ShouldConnect(world->GetTile(GetXpos(), GetYpos() - 1)));
    SetHasEastConnection(this->ShouldConnect(world->GetTile(GetXpos() + 1, GetYpos())));
    SetHasSouthConnection(this->ShouldConnect(world->GetTile(GetXpos(), GetYpos() + 1)));
    SetHasWestConnection(this->ShouldConnect(world->GetTile(GetXpos() - 1, GetYpos())));
}
