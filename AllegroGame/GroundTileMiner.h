#pragma once

#include "GroundTile.h"
#include "ItemInventory.h"

class GroundTileMiner
{
private:
	int miningDamageDone;
	ItemInventory* inventory;
	GroundTile* target;
	Tool* tool;
public:

	int GetMiningDamageDone() const;

	void SetTool(Tool* newTool);
	Tool* GetTool() const;

	ItemInventory* GetTargetItemInventory() const;
	void SetTargetItemInventory(ItemInventory* inv);

	void SetTarget(GroundTile* newTarget);
	GroundTile* GetTarget() const;

	void ResetProgress();

	void Mine();

	GroundTileMiner(Tool* t, ItemInventory* inv);

	~GroundTileMiner() = default;
};

