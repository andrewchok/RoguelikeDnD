#pragma once
#ifndef THUG
#define THUG
#include <string>
#include "EnemyCharacter.h"

class Thug : public EnemyCharacter
{
public:

	// ============================
	// ======== VARIABLES =========
	// ============================

	// ============================
	// ========= METHODS ==========
	// ============================

	Thug()
	{
		// Enemy Info
		token = 'T';
		name = "Thug";
		hitPoints = roll(5, 8) + 10;
		armorClass = 11;
		hasShield = false;
		speed = 30;
		OA_AC = armorClass - (speed - 30) / 5;
		expReward = 100;

		hitModifier = 4;

		// Stats
		STR = 15;
		DEX = 11;
		CON = 14;
		INT = 10;
		WIS = 10;
		CHA = 11;

		// Stat Modifiers
		int modSTR = statMod(STR);
		int modDEX = statMod(DEX);
		int modCON = statMod(CON);
		int modINT = statMod(INT);
		int modWIS = statMod(WIS);
		int modCHA = statMod(CHA);
	};
	~Thug() {};

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