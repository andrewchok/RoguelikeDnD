#pragma once
#include <string>
#ifndef ITEM
#define ITEM

class Item
{
public:

	std::string name = "item?";
	char token = '!';
	std::string description = "This is an item.";
	std::string itemType = "Generic Item";

	Item() {};
	~Item() {};
};

#endif