#pragma once
#include <string>
#include <allegro5/allegro5.h>
#include "json.h"


class Item
{
protected:
	int amount;
	std::string name;
	Item(std::string n);

public:

	virtual std::string GetID() const = 0;

	virtual std::string GetName() const;

	virtual int GetAmount() const;
	virtual void SetAmount(int a);

	virtual bool Equals(const Item& item) const;
	virtual bool Equals(const Item* item) const;

	virtual int AddAmount(int a);

	virtual void Draw(int x, int y, int width, int height) const = 0;

	~Item() = default;
};

Item* MakeItem(std::string id);
