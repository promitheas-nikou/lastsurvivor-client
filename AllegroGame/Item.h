#pragma once
#include <string>

class Item
{
protected:
	std::string name;
	Item(std::string n);

public:

	virtual int GetID() const = 0;

	virtual std::string GetName() const;
};

Item* MakeItem(int id);
