#pragma once
#include <string>
#include "json.h"
#include <allegro5/allegro.h>
#include "Tool.h"
#include "Item.h"

class World;

class GroundTile
{
protected:

	World* world;

	const int xpos, ypos;

	std::string name;

	ToolType requiredTool;

	GroundTile(World* w, int x, int y, std::string n);

public:
	virtual std::string GetID() const = 0;

	virtual std::string GetName() const;

	virtual void TickUpdate();
	virtual void TileUpdate();

	virtual void Draw() const = 0;

	virtual int GetMiningResistance() const;

	virtual ToolType GetRequiredToolType() const;

	virtual int GetDamageDealtByTool(Tool* tool) const;

	virtual Item* GetMiningResult(Tool* tool) const;

	int GetXpos() const;
	int GetYpos() const;

	virtual ~GroundTile() = default;
};

GroundTile* MakeGroundTile(World* world, std::string id, int x, int y);
