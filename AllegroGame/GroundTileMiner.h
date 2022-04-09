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

	virtual void AddResult(const ItemBundle* b);

	void ResetProgress();

	bool Mine();

	GroundTileMiner(Tool* t, ItemInventory* inv);

	virtual ~GroundTileMiner() = default;
};

