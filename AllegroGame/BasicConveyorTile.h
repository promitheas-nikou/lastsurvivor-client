#pragma once
#include "DirectedTile.h"
#include "LootBundle.h"
#include "FixedQueue.h"

class BasicConveyorTile :
    public DirectedTile
{
private:
    static int MINING_RESISTANCE;
    static ToolType TOOL_TYPE;
    static std::string NAME;
    static ALLEGRO_BITMAP* TEXTURES[16];
    static const LootBundle* DROP;
    static int CONVEYOR_MAX_ITEMS;
    static float CONVEYOR_ITEMS_DIST;
    static float CONVEYOR_SPEED;

    class ItemDescriptor {
    public:
        float prog;
        Direction from;
        Item* item;
        void SaveToFile(std::ofstream& file);
        static ItemDescriptor LoadFromFile(std::ifstream& file);
        ItemDescriptor(float p, Direction f, Item* i);
        ItemDescriptor() = default;
    };

    FixedQueue<ItemDescriptor> queue;
public:
    static const std::string ID;
    std::string GetID() const final;

    virtual bool IsTransparent() const final;
    virtual bool CanWalkThrough() const final;

    virtual ToolType GetOptimalToolType() const final;
    virtual float GetMiningResistance() const final;
    virtual std::string GetName() const final;

    virtual bool DoesTickUpdates() const final;
    virtual void TickUpdate(uint64_t T) final;

    virtual Tile* Clone(World* w, int x, int y) const final;
    virtual Tile* Clone(World* w, int x, int y, Direction d) const final;

    virtual Item* PushItem(Item* i, Direction d, ItemIOInterface* from) final;
    virtual Item* PullItem(Direction d, ItemIOInterface* to) final;

    void Draw() const final;
    void DrawOver() const final;

    virtual void WriteAdditionalDataToFile(std::ofstream& file) final;
    virtual void LoadAdditionalDataFromFile(std::ifstream& file) final;

    const ItemBundle* GetMiningResult(Tool* tool) const override;

    static void Init(nlohmann::json data);

    virtual ~BasicConveyorTile() = default;

    BasicConveyorTile(World* w, int x, int y);
    BasicConveyorTile(World* w, int x, int y, Direction d);
};

