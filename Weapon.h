#pragma once
#ifndef WEAPON
#define WEAPON

#include "Equipment.h"
#include "Enums.h"

class Weapon : public Equipment
{
public:

	dmgType damageType = dmgType::Acid;
	int diceType = 4;
	int numOfDice = 1;

	Weapon() {};
	~Weapon() {};
};

#endif