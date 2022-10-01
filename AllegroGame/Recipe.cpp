#include "Recipe.h"
#include "SimpleItemBundle.h"
#include "ItemIndex.h"
#include "Logging.h"

std::unordered_map<std::string, const SmeltingRecipe*> loaded_smelting_recipes;
std::unordered_map<std::string, const CraftingRecipe*> loaded_crafting_recipes;

CraftingRecipe::CraftingRecipe(nlohmann::json data)
{
    input = new SimpleItemBundle();
    output = new SimpleItemBundle();
    for (nlohmann::json item : data["input"])
        input->AddItem(MakeItemFromJSON(item));
    inputIndex = new ItemIndex(input);
    for (nlohmann::json item : data["output"])
        output->AddItem(MakeItemFromJSON(item));
    outputIndex = new ItemIndex(output);
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

bool CraftingRecipe::PerformOnInventories(ItemInventory* in, ItemInventory* out) const
{
    if (!in->ContainsItemIndexItems(inputIndex))
        return false;
    in->RemoveConstItemBundle(input);
    out->AddConstItemBundle(output);
    return true;
}

int CraftingRecipe::CheckTimesCanPerformOnInventory(ItemInventory* inventory) const
{
    return inventory->CountTimesContainsItemBundleItems(input);
}

void CraftingRecipe::LoadRecipes(nlohmann::json data)
{
    lsg_write_to_session_log(INFO,"Loading crafting recipes:");
    for (nlohmann::json rec : data)
    {
        loaded_crafting_recipes[rec["id"]] = new CraftingRecipe(rec);
        lsg_write_to_session_log(VERBOSE,"\tSuccessfully loaded crafting recipe #%s!", ((std::string)rec["id"]).c_str());
    }
    lsg_write_to_session_log(INFO, "Done loading crafting recipe!");
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
    input = MakeItemFromJSON(data["input"]);
    output = MakeItemFromJSON(data["output"]);
    duration = data.value("duration", 500);
}

const Item* SmeltingRecipe::GetInputItem() const
{
    return input;
}

const Item* SmeltingRecipe::GetOutputItem() const
{
    return output;
}

bool SmeltingRecipe::PerformOnInventories(ItemInventory* in, ItemInventory* out) const
{
    if(in->ContainsItem(input))
        if (out->CanAddConstItem(output))
        {
            in->RemoveConstItem(input);
            out->AddConstItem(output);
            return true;
        }
    return false;
}

bool SmeltingRecipe::CheckCanPerformOnInventories(ItemInventory* in, ItemInventory* out) const
{
    return (in->ContainsItem(input))&& (out->CanAddConstItem(output));
}

float SmeltingRecipe::GetDuration() const
{
    return duration;
}

void SmeltingRecipe::LoadRecipes(nlohmann::json data)
{
    lsg_write_to_session_log(INFO,"Loading smelting recipes:");
    for (nlohmann::json rec : data)
    {
        loaded_smelting_recipes[rec["id"]] = new SmeltingRecipe(rec);
        lsg_write_to_session_log(VERBOSE,"\tSuccessfully loaded smelting recipe #%s!", ((std::string)rec["id"]).c_str());
    }
    lsg_write_to_session_log(INFO, "Loading crafting recipes:");
}

void SmeltingRecipe::UnloadRecipes()
{
    for (const std::pair<std::string, const SmeltingRecipe*>& p : loaded_smelting_recipes)
        delete p.second;
    loaded_smelting_recipes.clear();
}

SmeltingRecipe::~SmeltingRecipe()
{
    delete input;
    delete output;
}
