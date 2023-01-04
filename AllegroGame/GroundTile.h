#pragma once
#include <string>
#include "json.h"
#include "ItemBundle.h"
#include <allegro5/allegro.h>
#include <fstream>
#include "Tool.h"
#include <unordered_map>
#include "Item.h"
#include "SoundType.h"
#include "LootBundle.h"

class World;
class PlayerEntity;

class GroundTile
{
protected:

	World* world;

	const int xpos, ypos;

	std::string name;

	Tool::ToolType requiredTool;

	GroundTile(World* w, int x, int y, std::string n, Tool::ToolType t);

public:
	virtual std::string GetID() const = 0;

	virtual void LoadAdditionalDataFromFile(std::ifstream& file);
	virtual void WriteAdditionalDataToFile(std::ofstream& file);

	virtual std::string GetName() const;

	virtual void TickUpdate();
	virtual void TileUpdate();

	virtual void Draw() const = 0;

	virtual GroundTile* Clone(World* w, int x, int y) const = 0;

	virtual int GetMiningResistance() const;

	virtual Tool::ToolType GetRequiredToolType() const;

	virtual int GetDamageDealtByTool(Tool* tool) const;
	virtual void Use(PlayerEntity* p);

	virtual const ItemBundle* GetMiningResult(Tool* tool) const;

	int GetXpos() const;
	int GetYpos() const;

    virtual float GetFrictionModifier() const;

	virtual void InitForWorld(World* w);

	virtual void PlaySound(SoundType t) const;

	virtual void RegisterLights();

	virtual ~GroundTile() = default;
};

GroundTile* MakeGroundTile(World* world, std::string id, int x, int y);


void InitAllGroundTilesForWorld(World* w);

extern std::unordered_map<std::string, const GroundTile*> prototype_gtiles;