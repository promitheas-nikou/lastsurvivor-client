io.write("Tile Name: ")
tileName = io.read('*l')
io.write("Class Name: ")
classname = io.read('*l')
io.write("ID: ")
tileID = io.read('*l')
io.write("Mining Resistance: ")
miningResistance = io.read('*l')
io.write("Correct Tool: ")
correctTool = io.read('*l')
io.write("Mining Drop: ")
miningDrop = io.read('*l')

function interp(s, tab)
  return (s:gsub('($%b{})', function(w) return tab[w:sub(3, -2)] or w end))
end

header = io.open("AllegroGame/"..classname..'.h','w')
code = io.open("AllegroGame/"..classname..'.cpp','w')
itemslistf = io.open("AllegroGame/ListAllTiles.h",'a')

header:write(
	interp(
		[[#pragma once
#include "Tile.h"
#include "LootBundle.h"
class ${classname} :
    public Tile
{
private:
    static float MINING_RESISTANCE;
    static ToolType TOOL_TYPE;
    static std::string NAME;
    static ALLEGRO_BITMAP* TEXTURE;
    static const LootBundle* DROP;
public:
    static const std::string ID;
    std::string GetID() const final;

    virtual bool IsTransparent() const final;
    virtual bool CanWalkThrough() const final;

    virtual ToolType GetOptimalToolType() const final;
    virtual float GetMiningResistance() const final;
    virtual std::string GetName() const final;

    virtual Tile* Clone(World* w, int x, int y, Direction d) const final;

    void Draw() const final;

    const ItemBundle* GetMiningResult(Tool* tool) const override;

    static void Init(nlohmann::json data);

    virtual ~${classname}() = default;

    ${classname}(World* w, int x, int y);
};


		]],
	_G)
)
header:flush()
header:close()

code:write(
	interp(
		[=[#include "${classname}.h"
#include "ResourceLoader.h"
#include "PlayerEntity.h"
#include "World.h"

int ${classname}::MINING_RESISTANCE;
ToolType ${classname}::TOOL_TYPE;
std::string ${classname}::NAME;
ALLEGRO_BITMAP* ${classname}::TEXTURE;
const std::string ${classname}::ID = "${tileID}";
const LootBundle* ${classname}::DROP;

std::string ${classname}::GetID() const
{
    return ID;
}

bool ${classname}::IsTransparent() const
{
    return false;
}

bool ${classname}::CanWalkThrough() const
{
    return false;
}

ToolType ${classname}::GetOptimalToolType() const
{
    return TOOL_TYPE;
}

int ${classname}::GetMiningResistance() const
{
    return MINING_RESISTANCE;
}

std::string ${classname}::GetName() const
{
    return NAME;
}

Tile* ${classname}::Clone(World* w, int x, int y, Direction d) const
{
    return new ${classname}(w, x, y);
}

const ItemBundle* ${classname}::GetMiningResult(Tool* tool) const
{
    return ${classname}::DROP->ConstCollapseToItemBundle();
}

void ${classname}::Draw() const
{
    al_draw_bitmap(TEXTURE, xpos * 128, ypos * 128, 0);
}

void ${classname}::Init(nlohmann::json data)
{
    TEXTURE = game_GetTexture(data[DATA_JSON_TEXTURE_KEY]);
    MINING_RESISTANCE = data[DATA_JSON_MINING_RESISTANCE_KEY];
    TOOL_TYPE = Tool::GetToolTypeFromString(data[DATA_JSON_TOOL_TYPE_KEY]);
    NAME = data[DATA_JSON_NAME_KEY];
    DROP = game_GetLootBundle(data[DATA_JSON_DROP_KEY]);
}


${classname}::${classname}(World* w, int x, int y): Tile(w, x, y)
{

}
]=],
	_G)
)

code:flush()
code:close()

itemslistf:write("\n#include \""..classname..".h\"\n")

print(
	interp(
		[[,
    {
      "id": "${tileID}",
      "mining_resistance": ${miningResistance},
      "name": "${tileName}",
      "tool": "${correctTool}",
      "texture": "tex.${tileID}",
      "drops": "${miningDrop}"
    }]],
	_G)
)


os.execute("pause")
