#pragma once
#include "LootBundle.h"
#include <vector>

class WeightedLootBundle :
    public LootBundle
{
private:
    class WeightedLootObject {
    private:
        int weight;
        LootObject* object;
    public:

        void AddConstToInventory(ItemInventory* inv) const;

        int GetWeight() const;
        LootObject* GetLootObject() const;

        WeightedLootObject(LootObject* o, int w);
    };

    std::vector<WeightedLootObject> objects;
    int totalWeight;

    void AddWeightedItem(Item* item, int weight);
public:

    virtual LootBundle* Clone() const final;
    virtual void AddConstToInventory(ItemInventory* inv) const final;
    virtual ItemBundle* ConstCollapseToItemBundle() const final;

    WeightedLootBundle() = default;
    WeightedLootBundle(const WeightedLootBundle&) = default;

    virtual ~WeightedLootBundle() = default;
};

