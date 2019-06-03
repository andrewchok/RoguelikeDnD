#pragma once
#ifndef ORC
#define ORC
#include <string>
#include "EnemyCharacter.h"

class Orc : public EnemyCharacter
{
public:

	// ============================
	// ======== VARIABLES =========
	// ============================

	// ============================
	// ========= METHODS ==========
	// ============================

	Orc()
	{
		// Enemy Info
		token = 'O';
		name = "Orc";
		hitPoints = roll(2, 8) + 6;
		armorClass = 13;
		hasShield = false;
		speed = 30;
		OA_AC = armorClass - (speed - 30) / 5;
		expReward = 100;

		// Stats
		STR = 16;
		DEX = 12;
		CON = 16;
		INT = 7;
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
	~Orc() {};

	int crit()
	{
		return roll(1, 12);
	};

	int attack()
	{
		int roll = roll20();
		return (roll == NAT_20) ? NAT_20 : roll + 5;
	};

	int damage()
	{
		return roll(1, 12) + 3;
	};

	void move() {};
	void idle() {};
	bool canSeePlayer() { return true; };
};

#endif