#pragma once
#include "UsableItem.h"

class WoodenHoeItem:
	public UsableItem
{
private:
	static std::string NAME;
	static std::string DESCRIPTION;
	static ALLEGRO_BITMAP* TEXTURE;
public:
	static const std::string ID;

	WoodenHoeItem();

	virtual std::string GetID() const final;

	virtual bool Use(float xpos, float ypos, PlayerEntity* player) final;

	virtual Item* Clone() const override;

	void Draw(int x, int y, int width, int height) const final;

	static void Init(nlohmann::json data);

	virtual ~WoodenHoeItem() = default;

};

