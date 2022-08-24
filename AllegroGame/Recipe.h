#pragma once
#include <vector>
#include <unordered_map>
#include "ItemBundle.h"
#include "ItemInventory.h"

class CraftingRecipe;
class SmeltingRecipe;

extern std::unordered_map<std::string, const SmeltingRecipe*> loaded_smelting_recipes;
extern std::unordered_map<std::string, const CraftingRecipe*> loaded_crafting_recipes;


class CraftingRecipe
{
private:
	int tier;
	ItemBundle* input;
	ItemBundle* output;

	CraftingRecipe(nlohmann::json data);

public:

	const ItemBundle* GetInputItems() const;
	const ItemBundle* GetOutputItems() const;

	int GetTier() const;


	bool PerformOnInventory(ItemInventory* inventory) const;

	int CheckTimesPerformOnInventory(ItemInventory* inventory) const;

	static void LoadRecipes(nlohmann::json data);
	static void UnloadRecipes();

	~CraftingRecipe();
};


class SmeltingRecipe
{
private:
	int tier;
	float minHeat;
	float duration;
	Item* inputItem;
	Item* outputItem;

	SmeltingRecipe(nlohmann::json data);

public:

	const Item* GetInputItem() const;
	const Item* GetOutputItem() const;


	float GetMinimumHeat() const;
	int GetTier() const;

	static void LoadRecipes(nlohmann::json data);
	static void UnloadRecipes();

	~SmeltingRecipe();
};

