#pragma once
#include <string>
#include <allegro5/allegro5.h>


class Item
{
protected:
	int amount;
	std::string name;
	Item(std::string n);

public:

	virtual int GetID() const = 0;

	virtual std::string GetName() const;

	virtual ALLEGRO_BITMAP* GetTexture() const = 0;

	virtual int GetAmount() const;
	virtual void SetAmount(int a);

	virtual bool Equals(const Item& item) const;
	virtual bool Equals(const Item* item) const;

	virtual int AddAmount(int a);

	virtual void Draw(int x, int y, int width, int height) const;

	~Item() = default;
};

Item* MakeItem(int id);
