#pragma once

#include "GroundTile.h"
#include "ItemInventory.h"
class World;

class GroundTileMiner
{
private:
	World *world;
	int miningDamageDone;
	ItemInventory* inventory;
	int gtileX;
	int gtileY;
	Tool* tool;
public:

	int GetMiningDamageDone() const;

	void SetTool(Tool* newTool);
	Tool* GetTool() const;

	ItemInventory* GetTargetItemInventory() const;
	void SetTargetItemInventory(ItemInventory* inv);

	void SetTarget(World* w, int x, int y);
	GroundTile* GetTarget() const;

	virtual void AddResult(const ItemBundle* b);

	void ResetProgress();

	bool Mine();

	GroundTileMiner(Tool* t, ItemInventory* inv, World* w, int x, int y);

	virtual ~GroundTileMiner() = default;
};

