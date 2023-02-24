#pragma once
#include "Tile.h"
class ConnectingTile :
    public Tile
{
private:
    char connections; //NULL,NULL,NULL,NULL,NORTH,EAST,SOUTH,WEST

    static constexpr char NORTH_MASK = 0b00001000;
    static constexpr char EAST_MASK = 0b00000100;
    static constexpr char SOUTH_MASK = 0b00000010;
    static constexpr char WEST_MASK = 0b00000001;

protected:

    char GetConnectionsChar() const;

    void SetHasNorthConnection(bool c);
    void SetHasEastConnection(bool c);
    void SetHasSouthConnection(bool c);
    void SetHasWestConnection(bool c);

public:

    bool HasNorthConnection() const;
    bool HasEastConnection() const;
    bool HasSouthConnection() const;
    bool HasWestConnection() const;

    ConnectingTile(World* w, int x, int y, char connections = 0);

    virtual bool ShouldConnect(Tile* tile) const;

    virtual void SerializeToStream(std::ostream& file) override;
    virtual void DeserializeFromStream(std::istream& file) override;

    virtual void TileUpdate() override;

    virtual ~ConnectingTile() = default;
};

