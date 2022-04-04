#pragma once
#include <string>
#include "json.h"
#include "Item.h"
#include "Tool.h"
#include <fstream>
#include <allegro5/allegro.h>

#include "ItemBundle.h"

class World;

class Tile
{
	protected:
		World* world;

		const int xpos, ypos;

		ToolType optimalToolType;

		int miningResistance;
		mutable int miningDamageDone;

		std::string name;

		Tile(World* w, int x, int y, ToolType t, int miningResistance, std::string n);

		Tile(World* w, int x, int y);

	public:
		virtual std::string GetID() const = 0;

		virtual void LoadAdditionalDataFromFile(std::ifstream &file);
		virtual void WriteAdditionalDataToFile(std::ofstream& file);

		virtual std::string GetName() const;

		virtual void TickUpdate();
		virtual void RandomTickUpdate();
		virtual void TileUpdate();

		virtual void Draw() const = 0;

		virtual bool canWalkThrough() const;
		virtual bool canSwimThrough() const;
		virtual bool canFlyThrough() const;
		virtual bool IsTransparent() const;
		virtual bool IsEmpty() const;

		virtual bool MineWithTool(Tool* tool);

		virtual const ItemBundle* GetMiningResult(Tool* tool) const;

		virtual int GetMiningResistance() const;
		virtual int GetMiningDamageDone() const;
		virtual ToolType GetOptimalToolType() const;

		int GetXpos() const;
		int GetYpos() const;

		virtual ~Tile() = default;
	};

Tile* MakeTile(World* world, std::string id, int x, int y);
