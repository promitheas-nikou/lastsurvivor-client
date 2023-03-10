#pragma once
#include "GroundTile.h"
#include "ItemBundle.h"
#include "AudioMultiTrackCollection.h"
#include "LootBundle.h"
#undef PlaySound

class DirtGroundTile :
    public GroundTile
{
private:
	static std::string NAME;
	static ALLEGRO_BITMAP* TEXTURES[2];
	static const LootBundle* DROP;
	static int MINING_RESISTANCE;
	static ToolType TOOL_TYPE;
	static AudioMultiTrackCollection AUDIO_TRACKS;
	bool isTilled = false;
public:
	static const std::string ID;

	std::string GetID() const final;

	virtual GroundTile* Clone(World* w, int x, int y) const final;

	DirtGroundTile(World* w, int x, int y);

	static void Init(nlohmann::json data);
	void Draw() const final;

	virtual void Till() final;
	virtual bool IsTillable() const final;
	virtual bool DoesSupportPlants() const final;

	const ItemBundle* GetMiningResult(Tool* tool) const final;

	virtual void PlaySound(SoundType t) const override;

	int GetMiningResistance() const final;

	virtual ~DirtGroundTile() = default;
};

