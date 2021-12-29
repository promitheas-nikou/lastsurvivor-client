#pragma once
#include <string>
#include <allegro5/allegro5.h>


class Item
{
protected:
	std::string name;
	Item(std::string n);

public:

	virtual int GetID() const = 0;

	virtual std::string GetName() const;

	virtual ALLEGRO_BITMAP* GetTexture() const = 0;

	virtual void Draw(int x, int y, int width, int height) const;
};

Item* MakeItem(int id);
