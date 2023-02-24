#pragma once

#include "SimpleUsableConsumableItem.h"

class FlaskItem :
	public UsableConsumableItem
{
private:
	static std::string NAME;
	static std::string DESCRIPTION;
	static ALLEGRO_BITMAP* TEXTURE;
	static int MAX_DURABILITY;
	static float HEALTH;
	static float HUNGER;
	static float WATER;
	int durability;

public:

	static const std::string ID;

	std::string GetID() const final;

	virtual int GetMaxStackSize() const final;

	FlaskItem();

	virtual void SaveToFile(std::ostream& file) final;
	virtual void DeserializeFromStream(std::istream& file) final;

	virtual float GetHealthBoost() const final;
	virtual float GetFoodBoost() const final;
	virtual float GetWaterBoost() const final;

	virtual bool Consume(float xpos, float ypos, PlayerEntity* player) final;

	virtual bool Use(float xpos, float ypos, PlayerEntity* player) final;

	virtual Item* Clone() const override;

	void Draw(int x, int y, int width, int height) const final;

	static void Init(nlohmann::json data);

	virtual ~FlaskItem() = default;

};

		