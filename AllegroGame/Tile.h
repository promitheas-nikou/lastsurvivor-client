#pragma once
#include <string>
#include "json.h"
#include <allegro5/allegro.h>

class World;

class Tile
{
	protected:
		World* world;

		const int xpos, ypos;

		std::string name;

		Tile(World* w, int x, int y, std::string n);

		virtual ALLEGRO_BITMAP* GetTexture() const;

	public:
		virtual int GetID() const = 0;

		virtual std::string GetName() const;

		virtual void TickUpdate();
		virtual void TileUpdate();

		virtual void Draw() const;

		virtual bool IsTransparent() const;
		virtual bool IsEmpty() const;



		virtual int GetMiningResistance() const;

		int GetXpos() const;
		int GetYpos() const;
	};

Tile* MakeTile(World* world, int id, int x, int y);
