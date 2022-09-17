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
	ItemIndex* inputIndex;
	ItemIndex* outputIndex;
	ItemBundle* input;
	ItemBundle* output;

	CraftingRecipe(nlohmann::json data);

public:

	const ItemBundle* GetInputItems() const;
	const ItemBundle* GetOutputItems() const;

	int GetTier() const;


	bool PerformOnInventories(ItemInventory* in, ItemInventory* out) const;
	int CheckTimesCanPerformOnInventory(ItemInventory* in) const;

	static void LoadRecipes(nlohmann::json data);
	static void UnloadRecipes();

	~CraftingRecipe();
};


class SmeltingRecipe
{
private:
	float duration;
	Item* input;
	Item* output;

	SmeltingRecipe(nlohmann::json data);

public:

	const Item* GetInputItem() const;
	const Item* GetOutputItem() const;

	bool PerformOnInventories(ItemInventory* in, ItemInventory* out) const;
	bool CheckCanPerformOnInventories(ItemInventory* in, ItemInventory* out) const;

	float GetDuration() const;

	static void LoadRecipes(nlohmann::json data);
	static void UnloadRecipes();

	~SmeltingRecipe();
};

