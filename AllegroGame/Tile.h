#pragma once
#include <string>
#include "json.h"
#include "Item.h"
#include "Tool.h"
#include <unordered_map>
#include <fstream>
#include <allegro5/allegro.h>

#include "ItemBundle.h"

class World;

class PlayerEntity;

class Tile
{
	protected:
		World* world;

		const int xpos, ypos;

		mutable int miningDamageDone;

		Tile(World* w, int x, int y);

	public:
		virtual std::string GetID() const = 0;

		virtual void LoadAdditionalDataFromFile(std::ifstream &file);
		virtual void WriteAdditionalDataToFile(std::ofstream& file);

		virtual std::string GetName() const = 0;

		virtual void TickUpdate();
		virtual void RandomTickUpdate();
		virtual void TileUpdate();

		virtual void Draw() const = 0;

		virtual Tile* Clone(World* w, int x, int y) const = 0;

		virtual bool CanWalkThrough() const;
		virtual bool canSwimThrough() const;
		virtual bool canFlyThrough() const;
		virtual bool IsTransparent() const;
		virtual bool IsEmpty() const;

		virtual void Use(PlayerEntity* user);

		virtual bool MineWithTool(Tool* tool);

		virtual const ItemBundle* GetMiningResult(Tool* tool) const;

		virtual int GetMiningResistance() const = 0;
		virtual ToolType GetOptimalToolType() const = 0;
		virtual int GetMiningDamageDone() const;

		int GetXpos() const;
		int GetYpos() const;

		virtual ~Tile() = default;
	};

Tile* MakeTile(World* world, std::string id, int x, int y);

extern std::unordered_map<std::string, const Tile*> prototype_tiles;
