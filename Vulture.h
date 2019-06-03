#pragma once
#ifndef VULTURE
#define VULTURE
#include <string>
#include "EnemyCharacter.h"

class Vulture : public EnemyCharacter
{
public:

	// ============================
	// ======== VARIABLES =========
	// ============================

	// ============================
	// ========= METHODS ==========
	// ============================

	Vulture()
	{
		// Enemy Info
		token = 'V';
		name = "Vulture";
		hitPoints = roll(1, 8) + 1;
		armorClass = 10;
		hasShield = false;
		speed = 50;
		OA_AC = armorClass - (speed - 30) / 5;
		expReward = 10;

		// Stats
		STR = 7;
		DEX = 10;
		CON = 13;
		INT = 2;
		WIS = 12;
		CHA = 4;

		// Stat Modifiers
		int modSTR = statMod(STR);
		int modDEX = statMod(DEX);
		int modCON = statMod(CON);
		int modINT = statMod(INT);
		int modWIS = statMod(WIS);
		int modCHA = statMod(CHA);
	};
	~Vulture() {};

	int crit()
	{
		return roll(1, 4);
	};

	int attack()
	{
		int roll = roll20();
		return (roll == NAT_20) ? NAT_20 : roll + 2;
	};

	int damage()
	{
		return roll(1, 4);
	};

	void move() {};
	void idle() {};
	bool canSeePlayer() { return true; };
};

#endif