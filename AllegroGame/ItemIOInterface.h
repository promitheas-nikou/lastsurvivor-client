#pragma once
#include "Directions.h"
class Item;

class ItemIOInterface {
	/*
	* ItemIOInterface from is pushing item i, FROM direction d (so from is `d` relative to `this`).
	*/
	virtual Item* PushItem(Item* i, Direction d, ItemIOInterface* from) = 0;
	virtual Item* PullItem(Direction d, ItemIOInterface* to) = 0;

};