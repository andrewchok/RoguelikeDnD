#pragma once
#ifndef BUGBEAR
#define BUGBEAR
#include <string>
#include "EnemyCharacter.h"

class Bugbear : public EnemyCharacter
{
public:

	// ============================
	// ======== VARIABLES =========
	// ============================

	// ============================
	// ========= METHODS ==========
	// ============================

	Bugbear()
	{
		// Enemy Info
		token = 'B';
		name = "Bugbear";
		hitPoints = roll(5, 8) + 5;
		armorClass = 14;
		hasShield = true;
		speed = 30;
		OA_AC = armorClass - (speed - 30) / 5;
		expReward = 200;

		// Stats
		STR = 15;
		DEX = 14;
		CON = 13;
		INT = 8;
		WIS = 11;
		CHA = 9;

		// Stat Modifiers
		int modSTR = statMod(STR);
		int modDEX = statMod(DEX);
		int modCON = statMod(CON);
		int modINT = statMod(INT);
		int modWIS = statMod(WIS);
		int modCHA = statMod(CHA);
	};
	~Bugbear() {};

	int crit()
	{
		return roll(1, 8);
	};

	int attack()
	{
		int roll = roll20();
		return (roll == NAT_20) ? NAT_20 : roll + 4;
	};

	int damage()
	{
		return roll(2, 8) + 2; // brute: rolls an extra die for damage
	};

	void move() {};
	void idle() {};
	bool canSeePlayer() { return true; };
};

#endif