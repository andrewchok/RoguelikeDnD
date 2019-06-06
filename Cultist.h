#pragma once
#ifndef CULTIST
#define CULTIST
#include <string>
#include "EnemyCharacter.h"

class Cultist : public EnemyCharacter
{
public:

	// ============================
	// ======== VARIABLES =========
	// ============================

	// ============================
	// ========= METHODS ==========
	// ============================

	Cultist()
	{
		// Enemy Info
		token = 'C';
		name = "Cultist";
		hitPoints = roll(2, 8);
		armorClass = 12;
		hasShield = false;
		speed = 30;
		OA_AC = armorClass - (speed - 30) / 5;
		expReward = 25;

		hitModifier = 3;

		// Stats
		STR = 11;
		DEX = 12;
		CON = 10;
		INT = 10;
		WIS = 11;
		CHA = 10;

		// Stat Modifiers
		int modSTR = statMod(STR);
		int modDEX = statMod(DEX);
		int modCON = statMod(CON);
		int modINT = statMod(INT);
		int modWIS = statMod(WIS);
		int modCHA = statMod(CHA);
	};
	~Cultist() {};

	int crit()
	{
		return roll(1, 6);
	};

	int damage()
	{
		return roll(1, 6) + 1;
	};
};

#endif