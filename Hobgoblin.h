#pragma once
#ifndef HOBGOBLIN
#define HOBGOBLIN
#include <string>
#include "EnemyCharacter.h"

class Hobgoblin : public EnemyCharacter
{
public:

	// ============================
	// ======== VARIABLES =========
	// ============================

	// ============================
	// ========= METHODS ==========
	// ============================

	Hobgoblin()
	{
		// Enemy Info
		token = 'H';
		name = "Hobgoblin";
		hitPoints = roll(2, 8) + 2;
		armorClass = 16;
		hasShield = true;
		speed = 30;
		OA_AC = armorClass - (speed - 30) / 5;
		expReward = 100;

		// Stats
		STR = 13;
		DEX = 12;
		CON = 12;
		INT = 10;
		WIS = 10;
		CHA = 9;

		// Stat Modifiers
		int modSTR = statMod(STR);
		int modDEX = statMod(DEX);
		int modCON = statMod(CON);
		int modINT = statMod(INT);
		int modWIS = statMod(WIS);
		int modCHA = statMod(CHA);
	};
	~Hobgoblin() {};

	int crit()
	{
		return roll(1, 8);
	};

	int attack()
	{
		int roll = roll20();
		return (roll == NAT_20) ? NAT_20 : roll + 3;
	};

	int damage()
	{
		return roll(1, 8) + 1;
	};

	void move() {};
	void idle() {};
	bool canSeePlayer() { return true; };
};

#endif