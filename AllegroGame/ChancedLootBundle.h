#pragma once
#include "LootBundle.h"

class ChancedLootBundle :
    public LootBundle
{
private:
    class ChancedLootObject {
    private:
        LootObject* object;
        float chance;
    public:
        ChancedLootObject(LootObject* o, float c);
        
        void AddConstToInventory(ItemInventory* inv) const;
        ItemBundle* CollapseToItemBundle() const;
    };

    void AddChancedLootObject(LootObject* obj, float chance);

    std::vector<ChancedLootObject> objects;
public:

    virtual LootBundle* Clone() const final;
    virtual void AddConstToInventory(ItemInventory* inv) const final;
    virtual ItemBundle* ConstCollapseToItemBundle() const final;

    ChancedLootBundle() = default;
    ChancedLootBundle(const ChancedLootBundle&) = default;

    virtual ~ChancedLootBundle() = default;

    friend LootBundle;
};

