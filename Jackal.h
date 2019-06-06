#pragma once
#ifndef JACKAL
#define JACKAL
#include <string>
#include "EnemyCharacter.h"

class Jackal : public EnemyCharacter
{
public:

	// ============================
	// ======== VARIABLES =========
	// ============================

	// ============================
	// ========= METHODS ==========
	// ============================

	Jackal()
	{
		// Enemy Info
		token = 'J';
		name = "Jackal";
		hitPoints = roll(1, 6);
		armorClass = 12;
		hasShield = false;
		speed = 40;
		OA_AC = armorClass - (speed - 30) / 5;
		expReward = 10;

		hitModifier = 1;

		// Stats
		STR = 8;
		DEX = 15;
		CON = 11;
		INT = 3;
		WIS = 12;
		CHA = 6;

		// Stat Modifiers
		int modSTR = statMod(STR);
		int modDEX = statMod(DEX);
		int modCON = statMod(CON);
		int modINT = statMod(INT);
		int modWIS = statMod(WIS);
		int modCHA = statMod(CHA);
	};
	~Jackal() {};

	int crit()
	{
		return roll(1, 4);
	};

	int damage()
	{
		return roll(1, 4) - 1;
	};
};

#endif