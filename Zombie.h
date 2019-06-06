#pragma once
#ifndef ZOMBIE
#define ZOMBIE
#include <string>
#include "EnemyCharacter.h"

class Zombie : public EnemyCharacter
{
public:

	// ============================
	// ======== VARIABLES =========
	// ============================

	// ============================
	// ========= METHODS ==========
	// ============================

	Zombie()
	{
		// Enemy Info
		token = 'Z';
		name = "Zombie";
		hitPoints = roll(3, 8) + 9;
		armorClass = 8;
		hasShield = false;
		speed = 20;
		OA_AC = armorClass - (speed - 30) / 5;
		expReward = 50;

		hitModifier = 3;

		// Stats
		STR = 13;
		DEX = 6;
		CON = 16;
		INT = 3;
		WIS = 6;
		CHA = 5;

		// Stat Modifiers
		int modSTR = statMod(STR);
		int modDEX = statMod(DEX);
		int modCON = statMod(CON);
		int modINT = statMod(INT);
		int modWIS = statMod(WIS);
		int modCHA = statMod(CHA);
	};
	~Zombie() {};

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