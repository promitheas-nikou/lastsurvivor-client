#pragma once
#include "GroundTile.h"
class StoneGroundTile:
	public GroundTile
{
private:
	static std::string NAME;
	static ALLEGRO_BITMAP* TEXTURE;
	static const ItemBundle* DROP;
	static int MINING_RESISTANCE;
	static ToolType TOOL_TYPE;
public:
	static const std::string ID;

	std::string GetID() const final;

	StoneGroundTile(World* w, int x, int y);

	static void Init(nlohmann::json data);

	void Draw() const final;

	virtual GroundTile* Clone(World* w, int x, int y) const final;

	const ItemBundle* GetMiningResult(Tool* tool) const final;

	int GetMiningResistance() const final;

	virtual ~StoneGroundTile() = default;
};

