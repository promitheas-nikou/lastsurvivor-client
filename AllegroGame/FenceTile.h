#pragma once
#include "ConnectingTile.h"
class FenceTile :
	public ConnectingTile
{
private:
	static ALLEGRO_BITMAP* TEXTURES[16];
	static ToolType TOOL_TYPE;
	static int MINING_RESISTANCE;
	static std::string NAME;
public:
	static const std::string ID;

	std::string GetID() const final;

	virtual bool IsTransparent() const final;
	virtual bool CanWalkThrough() const final;

	virtual ToolType GetOptimalToolType() const final;
	virtual int GetMiningResistance() const final;
	virtual std::string GetName() const final;

	virtual bool ShouldConnect(Tile* t) const final;

	void Draw() const final;

	virtual Tile* Clone(World* w, int x, int y) const final;

	static void Init(nlohmann::json data);

	virtual ~FenceTile() = default;

	FenceTile(World * w, int x, int y, char connections = 0);
};

