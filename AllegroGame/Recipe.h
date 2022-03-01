#pragma once
#include <vector>
#include <unordered_map>
#include "ItemBundle.h"
#include "ItemInventory.h"

class Recipe;

extern std::unordered_map<std::string, const Recipe*> loaded_hand_crafting_recipes;
extern std::unordered_map<std::string, const Recipe*> loaded_smelting_recipes;
extern std::unordered_map<std::string, const Recipe*> loaded_crafting_recipes;


class Recipe
{
private:
	ItemBundle* input;
	ItemBundle* output;

	Recipe(nlohmann::json data);

public:

	const ItemBundle* GetInputItems() const;
	const ItemBundle* GetOutputItems() const;

	bool PerformOnInventory(ItemInventory* inventory) const;

	static void LoadRecipes(nlohmann::json data);
	static void UnloadRecipes();

	~Recipe();
};

