#pragma once
#ifndef KOBOLD
#define KOBOLD
#include <string>
#include "EnemyCharacter.h"

class Kobold : public EnemyCharacter
{
public:

	// ============================
	// ======== VARIABLES =========
	// ============================

	// ============================
	// ========= METHODS ==========
	// ============================

	Kobold()
	{
		// Enemy Info
		token = 'K';
		name = "Kobold";
		hitPoints = roll(1, 6) - 2;
		while (hitPoints == 0) hitPoints = roll(1, 6) - 2;
		armorClass = 12;
		hasShield = false;
		speed = 30;
		OA_AC = armorClass - (speed - 30) / 5;
		expReward = 25;

		hitModifier = 4;

		// Stats
		STR = 7;
		DEX = 15;
		CON = 9;
		INT = 8;
		WIS = 7;
		CHA = 8;

		// Stat Modifiers
		int modSTR = statMod(STR);
		int modDEX = statMod(DEX);
		int modCON = statMod(CON);
		int modINT = statMod(INT);
		int modWIS = statMod(WIS);
		int modCHA = statMod(CHA);
	};
	~Kobold() {};

	int crit()
	{
		return roll(1, 4);
	};

	int damage()
	{
		return roll(1, 4) + 2;
	};
};

#endif