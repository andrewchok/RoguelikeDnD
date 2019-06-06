#pragma once
#ifndef GOLD
#define GOLD

#include "Helper.h"
#include "Item.h"

class Gold : public Item
{
public:

	Gold() 
	{
		name = "Gold";
		token = '$';
		description = "Everyone wants a purpose in life. Wrong. Just gold. Everyone wants gold.";
		itemType = "Currency";

		amount = randomNumber(5, 99);
	};
	~Gold() {};
};

#endif