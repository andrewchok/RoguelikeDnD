#pragma once
#ifndef RATION
#define RATION

#include "Item.h"

class Ration : public Item
{
public:

	Ration() 
	{
		name = "Ration";
		token = '&';
		description = "It ain't much but its honest food.";
		itemType = "food";
	};
	~Ration() {};
};

#endif