#include "Recipe.h"
#include "SimpleItemBundle.h"

std::unordered_map<std::string, const Recipe*> loaded_hand_crafting_recipes;
std::unordered_map<std::string, const Recipe*> loaded_smelting_recipes;
std::unordered_map<std::string, const Recipe*> loaded_crafting_recipes;

Recipe::Recipe(nlohmann::json data)
{
    input = new SimpleItemBundle();
    output = new SimpleItemBundle();
    for (nlohmann::json item : data["input"])
        input->AddItem(MakeItemFromJSON(item));
    for (nlohmann::json item : data["output"])
        output->AddItem(MakeItemFromJSON(item));
}

const ItemBundle* Recipe::GetInputItems() const
{
    return input;
}

const ItemBundle* Recipe::GetOutputItems() const
{
    return output;
}

bool Recipe::PerformOnInventory(ItemInventory* inventory) const
{
    if (!inventory->ContainsItemBundleItems(input))
        return false;
    inventory->RemoveConstItemBundle(input);
    inventory->AddConstItemBundle(output);
    return true;
}

void Recipe::LoadRecipes(nlohmann::json data)
{
    printf("Loading recipes:");
    for (nlohmann::json rec : data)
    {
        loaded_crafting_recipes[rec["id"]] = new Recipe(rec);
        printf("\tSuccessfully loaded recipe #%s!\n", ((std::string)rec["id"]).c_str());
    }

}

void Recipe::UnloadRecipes()
{
    for (const std::pair<std::string, const Recipe*>& p : loaded_hand_crafting_recipes)
        delete p.second;
    loaded_hand_crafting_recipes.clear();
    for (const std::pair<std::string, const Recipe*>& p : loaded_crafting_recipes)
        delete p.second;
    loaded_hand_crafting_recipes.clear();
    for (const std::pair<std::string, const Recipe*>& p : loaded_smelting_recipes)
        delete p.second;
    loaded_hand_crafting_recipes.clear();
    loaded_crafting_recipes.clear();
    loaded_smelting_recipes.clear();
}

Recipe::~Recipe()
{
    delete input;
    delete output;
}
