#pragma once
#include "ToolItem.h"
class WoodenShovelItem :
    public ToolItem
{
private:
    static std::string NAME;
    static std::string DESCRIPTION;
    static ALLEGRO_BITMAP* TEXTURE;
    static float MINING_DAMAGE;
    static int MINING_LEVEL;
    static Tool::ToolType MINING_TYPE;

public:

    static const std::string ID;

    std::string GetID() const final;

    virtual     float GetMiningDamage() const final;
    virtual Tool::ToolType GetToolType() const final;
    virtual int GetMiningLevel() const final;
    WoodenShovelItem();

    virtual Item* Clone() const override;

    void Draw(int x, int y, int width, int height) const final;

    static void Init(nlohmann::json data);

    virtual ~WoodenShovelItem() = default;
};

