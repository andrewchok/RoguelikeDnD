#pragma once
#ifndef NIGHTMARE
#define NIGHTMARE
#include <string>
#include "EnemyCharacter.h"

class Nightmare : public EnemyCharacter
{
public:

	// ============================
	// ======== VARIABLES =========
	// ============================

	// ============================
	// ========= METHODS ==========
	// ============================

	Nightmare()
	{
		// Enemy Info
		token = 'N';
		name = "Nightmare";
		hitPoints = roll(8, 10) + 24;
		armorClass = 13;
		hasShield = false;
		speed = 90;
		OA_AC = armorClass - (speed - 30) / 5;
		expReward = 700;

		hitModifier = 6;

		// Stats
		STR = 18;
		DEX = 15;
		CON = 16;
		INT = 10;
		WIS = 13;
		CHA = 15;

		// Stat Modifiers
		int modSTR = statMod(STR);
		int modDEX = statMod(DEX);
		int modCON = statMod(CON);
		int modINT = statMod(INT);
		int modWIS = statMod(WIS);
		int modCHA = statMod(CHA);
	};
	~Nightmare() {};

	int crit()
	{
		return roll(2, 8);
	};

	int damage()
	{
		return roll(2, 8) + 4 + roll(2, 6);
	};
};

#endif