#pragma once

#include "Item.h"

class BoneItem :
	public Item
{
private:
	static std::string NAME;
	static std::string DESCRIPTION;
	static ALLEGRO_BITMAP* TEXTURE;

public:

	static const std::string ID;

	std::string GetID() const final;

	BoneItem();

	virtual Item* Clone() const override;

	void Draw(int x, int y, int width, int height) const final;

	static void Init(nlohmann::json data);

	virtual ~BoneItem() = default;

};

