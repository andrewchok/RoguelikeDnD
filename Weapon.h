#pragma once
#ifndef WEAPON
#define WEAPON

#include "Equipment.h"
#include "Helper.h"

class Weapon : public Equipment
{
public:

	DmgType damageType = DmgType::Acid;
	int diceType = 4;
	int numOfDice = 1;

	Weapon() {};
	~Weapon() {};
};

#endif