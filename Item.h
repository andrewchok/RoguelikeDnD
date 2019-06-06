#pragma once
#ifndef ITEM
#define ITEM

#include "Helper.h"

class Item
{
public:

	std::string name = "item?";
	char token = '!';
	std::string description = "This is an item.";
	std::string itemType = "Generic Item";

	// for Gold
	int amount = -9999;

	Coordinate location;

	Item() {};
	~Item() {};

	bool setLocation(int x_pos, int y_pos, Coordinate stairs_loc, Coordinate player_loc)
	{
		if (x_pos > 0 && x_pos < 80 && y_pos > 0 && y_pos < 23)
		{
			if (x_pos == stairs_loc.x && y_pos < stairs_loc.y) return false;
			if (x_pos == player_loc.x && y_pos < player_loc.y) return false;

			this->location.x = x_pos;
			this->location.y = y_pos;
			return true;
		}
		return false;
	};
};

#endif