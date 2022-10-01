#include "SimpleUsableConsumableItem.h"

SimpleUsableConsumableItem::SimpleUsableConsumableItem(float health, float hunger, float water) : SimpleConsumableItem(health, hunger, water), UsableConsumableItem()
{}

SimpleUsableConsumableItem::~SimpleUsableConsumableItem()
{}
