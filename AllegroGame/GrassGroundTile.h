#pragma once
#include "GroundTile.h"
#include "json.h"
#include "AudioMultiTrackCollection.h"
#include "LootBundle.h"
#undef PlaySound

class GrassGroundTile:
	public GroundTile
{
private:
	static std::string NAME;
	static ALLEGRO_BITMAP* TEXTURES[2];
	static const LootBundle* DROP;
	static int MINING_RESISTANCE;
	static ToolType TOOL_TYPE;
	static AudioMultiTrackCollection AUDIO_TRACKS;
public:
	static const std::string ID;

	std::string GetID() const final;

	GrassGroundTile(World* w, int x, int y);

	static void Init(nlohmann::json data);

	void Draw() const final;
	
	virtual GroundTile* Clone(World* w, int x, int y) const final;

	const ItemBundle* GetMiningResult(Tool* tool) const final;

	int GetMiningResistance() const final;

	virtual void PlaySound(SoundType t) const override;

	virtual ~GrassGroundTile() = default;
};

