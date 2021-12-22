#pragma once
#include <string>
#include "json.h"
#include <allegro5/allegro.h>

class GroundTile
{
protected:

	const int xpos, ypos;

	std::string name;

	GroundTile(int x, int y, std::string n);

	virtual ALLEGRO_BITMAP* GetTexture() const;

public:
	virtual int GetID() const = 0;

	virtual std::string GetName() const;

	virtual void TickUpdate();
	virtual void TileUpdate();

	virtual void Draw() const;

	virtual int GetMiningResistance() const;

	int GetXpos() const;
	int GetYpos() const;
};

GroundTile* MakeGroundTile(int id, int x, int y);
