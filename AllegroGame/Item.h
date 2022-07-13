#pragma once
#include <string>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include "json.h"
#include "LootObject.h"


class World;

class Item:
	public LootObject
{
protected:
	int amount;
	std::string name;
	Item(std::string n);

public:

	static constexpr int MAX_AMOUNT = 128;

	virtual void LoadAdditionalDataFromFile(std::ifstream &file);
	virtual void WriteAdditionalDataToFile(std::ofstream& file);

	virtual std::string GetID() const = 0;

	virtual std::string GetName() const;

	virtual int GetAmount() const;
	virtual int RemoveAmount(int targetAmount);
	virtual Item* SetAmount(int a);

	virtual bool Equals(const Item& item) const;
	virtual bool Equals(const Item* item) const;

	virtual ItemBundle* ConstCollapseToItemBundle() const final;

	virtual void AddConstToInventory(ItemInventory* inv) const override;

	virtual Item* Clone() const = 0;

	virtual int AddAmount(int a);

	virtual void UseOnTile(World* world, int x, int y);

	virtual void Draw(int x, int y, int width, int height) const = 0;
	virtual void DrawText(int x, int y, ALLEGRO_FONT* font, ALLEGRO_COLOR color, int align) const;
	virtual void DrawWithText(int x, int y, int width, int height) const;

	virtual ~Item() = default;
};

extern std::unordered_map<std::string, Item*> prototype_items;

Item* MakeItemFromID(std::string id);

Item* MakeItemFromJSON(nlohmann::json data);
