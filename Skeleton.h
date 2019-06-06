#pragma once
#ifndef SKELETON
#define SKELETON
#include <string>
#include "EnemyCharacter.h"

class Skeleton : public EnemyCharacter
{
public:

	// ============================
	// ======== VARIABLES =========
	// ============================

	// ============================
	// ========= METHODS ==========
	// ============================

	Skeleton()
	{
		// Enemy Info
		token = 'S';
		name = "Skeleton";
		hitPoints = roll(2, 8) + 4;
		armorClass = 13;
		hasShield = false;
		speed = 30;
		OA_AC = armorClass - (speed - 30) / 5;
		expReward = 50;

		hitModifier = 4;

		// Stats
		STR = 10;
		DEX = 14;
		CON = 15;
		INT = 6;
		WIS = 8;
		CHA = 5;

		// Stat Modifiers
		int modSTR = statMod(STR);
		int modDEX = statMod(DEX);
		int modCON = statMod(CON);
		int modINT = statMod(INT);
		int modWIS = statMod(WIS);
		int modCHA = statMod(CHA);
	};
	~Skeleton() {};

	int crit()
	{
		return roll(1, 6);
	};

	int damage()
	{
		return roll(1, 6) + 2;
	};
};

#endif