#pragma once
#ifndef WINTERWOLF
#define WINTERWOLF
#include <string>
#include "EnemyCharacter.h"

class WinterWolf : public EnemyCharacter
{
public:

	// ============================
	// ======== VARIABLES =========
	// ============================

	// ============================
	// ========= METHODS ==========
	// ============================

	WinterWolf()
	{
		// Enemy Info
		token = 'W';
		name = "WinterWolf";
		hitPoints = roll(10, 10) + 20;
		armorClass = 13;
		hasShield = false;
		speed = 50;
		OA_AC = armorClass - (speed - 30) / 5;
		expReward = 700;

		hitModifier = 3;

		// Stats
		STR = 18;
		DEX = 13;
		CON = 14;
		INT = 7;
		WIS = 12;
		CHA = 8;

		// Stat Modifiers
		int modSTR = statMod(STR);
		int modDEX = statMod(DEX);
		int modCON = statMod(CON);
		int modINT = statMod(INT);
		int modWIS = statMod(WIS);
		int modCHA = statMod(CHA);
	};
	~WinterWolf() {};

	int crit()
	{
		return roll(2, 8);
	};

	int damage()
	{
		return roll(4, 8);
	};
};

#endif