#pragma once
#include <string>
#include "json.h"
#include "Item.h"
#include "Tool.h"
#include <allegro5/allegro.h>

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

		virtual ALLEGRO_BITMAP* GetTexture() const;

	public:
		virtual int GetID() const = 0;

		virtual std::string GetName() const;

		virtual void TickUpdate();
		virtual void TileUpdate();

		virtual void Draw() const;

		virtual bool IsTransparent() const;
		virtual bool IsEmpty() const;

		virtual Item* MineTile();

		virtual bool MineWithTool(Tool* tool);

		virtual int GetMiningResistance() const;
		virtual int GetMiningDamageDone() const;
		virtual ToolType GetOptimalToolType() const;

		int GetXpos() const;
		int GetYpos() const;
	};

Tile* MakeTile(World* world, int id, int x, int y);
