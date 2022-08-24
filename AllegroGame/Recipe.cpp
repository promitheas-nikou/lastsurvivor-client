#include "Recipe.h"
#include "SimpleItemBundle.h"
#include "ItemIndex.h"

std::unordered_map<std::string, const SmeltingRecipe*> loaded_smelting_recipes;
std::unordered_map<std::string, const CraftingRecipe*> loaded_crafting_recipes;

CraftingRecipe::CraftingRecipe(nlohmann::json data)
{
    input = new SimpleItemBundle();
    output = new SimpleItemBundle();
    for (nlohmann::json item : data["input"])
        input->AddItem(MakeItemFromJSON(item));
    for (nlohmann::json item : data["output"])
        output->AddItem(MakeItemFromJSON(item));
    tier = data.value("tier",0);
}

const ItemBundle* CraftingRecipe::GetInputItems() const
{
    return input;
}

const ItemBundle* CraftingRecipe::GetOutputItems() const
{
    return output;
}
int CraftingRecipe::GetTier() const
{
    return tier;
}

bool CraftingRecipe::PerformOnInventory(ItemInventory* inventory) const
{
    if (!inventory->ContainsItemBundleItems(input))
        return false;
    inventory->RemoveConstItemBundle(input);
    inventory->AddConstItemBundle(output);
    return true;
}

int CraftingRecipe::CheckTimesPerformOnInventory(ItemInventory* inventory) const
{
    return inventory->CountTimesContainsItemBundleItems(input);
}

void CraftingRecipe::LoadRecipes(nlohmann::json data)
{
    printf("Loading crafting recipes:");
    for (nlohmann::json rec : data)
    {
        loaded_crafting_recipes[rec["id"]] = new CraftingRecipe(rec);
        printf("\tSuccessfully loaded crafting recipe #%s!\n", ((std::string)rec["id"]).c_str());
    }

}

void CraftingRecipe::UnloadRecipes()
{
    for (const std::pair<std::string, const CraftingRecipe*>& p : loaded_crafting_recipes)
        delete p.second;
    loaded_crafting_recipes.clear();
}

CraftingRecipe::~CraftingRecipe()
{
    delete input;
    delete output;
}

SmeltingRecipe::SmeltingRecipe(nlohmann::json data)
{
    inputItem = MakeItemFromJSON(data["input"]);
    outputItem = MakeItemFromJSON(data["output"]);
    tier = data.value("tier", 0);
    minHeat = data.value("minHeat", 100);
    duration = data.value("duration", 500);
}

const Item* SmeltingRecipe::GetInputItem() const
{
    return inputItem;
}

const Item* SmeltingRecipe::GetOutputItem() const
{
    return outputItem;
}

float SmeltingRecipe::GetMinimumHeat() const
{
    return minHeat;
}

int SmeltingRecipe::GetTier() const
{
    return tier;
}

void SmeltingRecipe::LoadRecipes(nlohmann::json data)
{
    printf("Loading smelting recipes:");
    for (nlohmann::json rec : data)
    {
        loaded_smelting_recipes[rec["id"]] = new SmeltingRecipe(rec);
        printf("\tSuccessfully loaded smelting recipe #%s!\n", ((std::string)rec["id"]).c_str());
    }
}

void SmeltingRecipe::UnloadRecipes()
{
    for (const std::pair<std::string, const SmeltingRecipe*>& p : loaded_smelting_recipes)
        delete p.second;
    loaded_smelting_recipes.clear();
}

SmeltingRecipe::~SmeltingRecipe()
{
    delete inputItem;
    delete outputItem;
}
