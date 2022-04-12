#pragma once
#include "GroundTile.h"
#include "ItemBundle.h"
#include "AudioMultiTrackCollection.h"

class DirtGroundTile :
    public GroundTile
{
private:
	static std::string NAME;
	static ALLEGRO_BITMAP* TEXTURE;
	static const ItemBundle* DROP;
	static int MINING_RESISTANCE;
	static ToolType TOOL_TYPE;
	static AudioMultiTrackCollection AUDIO_TRACKS;
public:
	static const std::string ID;

	std::string GetID() const final;

	DirtGroundTile(World* w, int x, int y);

	static void Init(nlohmann::json data);
	void Draw() const final;

	const ItemBundle* GetMiningResult(Tool* tool) const final;

	virtual void PlaySound(SoundType t) const override;

	int GetMiningResistance() const final;

	virtual ~DirtGroundTile() = default;
};

