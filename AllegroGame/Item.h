#pragma once
#include <string>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include "json.h"
#include <fstream>
#include "LootObject.h"


class World;

class Item:
	public LootObject
{
private:
protected:
	static int MLBUF;
	static bool DrawItemDetailsPaneMultilineCB(int line_num, const char* line, int size, void* extra);

	int amount;
	bool hasCustomName = false;
	std::string name;
	bool hasCustomDescription = false;
	std::string description;
	Item(std::string n, std::string d = "");

public:

	static std::unordered_map<std::string, uint32_t> str_to_id;
	static std::map<uint32_t, std::string> id_to_str;

	virtual int GetMaxStackSize() const;

	virtual std::string GetID() const = 0;

	virtual std::string GetName() const;
	virtual std::string GetDescription() const;

	virtual int GetAmount() const;
	virtual int RemoveAmount(int targetAmount);
	virtual Item* SetAmount(int a);

	virtual bool Equals(const Item& item) const;
	virtual bool Equals(const Item* item) const;

	virtual void DrawItemDetailsPane(int x, int y);

	virtual ItemBundle* ConstCollapseToItemBundle() const final;

	virtual void SaveToFile(std::ofstream &file);
	static void SaveToFile(Item* item, std::ofstream& file);
	static Item* LoadFromFile(std::ifstream& file);
	virtual void LoadAdditionalDataFromFile(std::ifstream &file);

	virtual void AddConstToInventory(ItemInventory* inv) const override;

	virtual Item* Clone() const = 0;

	virtual int AddAmount(int a);

	virtual void Draw(int x, int y, int width, int height) const = 0;
	virtual void DrawText(int x, int y, ALLEGRO_FONT* font, ALLEGRO_COLOR color, int align) const;
	virtual void DrawWithText(int x, int y, int width, int height) const;

	virtual ~Item() = default;
};

extern std::unordered_map<std::string, Item*> prototype_items;

Item* MakeItemFromID(std::string id);

Item* MakeItemFromJSON(nlohmann::json data);
