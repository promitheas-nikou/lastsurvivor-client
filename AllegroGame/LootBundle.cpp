#include "LootBundle.h"
#include "SimpleLootBundle.h"
#include "ChancedLootBundle.h"
#include "WeightedLootBundle.h"
#include "VariableAmountItem.h"

LootObject* CreateLootObjectFromJSON(nlohmann::json data) {

	if (data["type"] == "item")
	{
		return MakeItemFromID(data["id"])->SetAmountX(data["amount"]);
	}
	else if (data["type"] == "varamount_item")
	{
		int minamount = data["minamount"];
		int maxamount = data["maxamount"];
		return new VariableAmountItem(minamount, maxamount, data["id"]);
	}
	else if (data["type"] == "loot_bundle")
	{
		return LootBundle::CreateFromJSON(data["loot_bundle"]);
	}
}

LootBundle* LootBundle::CreateFromJSON(nlohmann::json data)
{
	std::string type = data["type"];
	nlohmann::json objects = data["objects"];
	if (type == "null")
	{
		return new SimpleLootBundle();
	}
	else if (type == "simple")
	{
		SimpleLootBundle* bundle = new SimpleLootBundle();
		for (nlohmann::json object : objects)
		{
			bundle->AddLootObject(CreateLootObjectFromJSON(object));
		}
		return bundle;
	}
	else if (type == "chanced")
	{
		ChancedLootBundle* bundle = new ChancedLootBundle();
		for (nlohmann::json object : objects)
		{
			bundle->AddChancedLootObject(CreateLootObjectFromJSON(object), object["chance"]);
		}
		return bundle;
	}
	else if (type == "weighted")
	{
		WeightedLootBundle* bundle = new WeightedLootBundle();
		for (nlohmann::json object : objects)
		{
			bundle->AddWeightedLootObject(CreateLootObjectFromJSON(object), object["weight"]);
		}
		return bundle;
	}
}
