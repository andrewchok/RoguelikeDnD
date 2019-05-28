#pragma once
#ifndef GOBLIN
#define GOBLIN
#include <string>
#include "EnemyCharacter.h"

class Goblin : public EnemyCharacter
{
public:

	// ============================
	// ======== VARIABLES =========
	// ============================

	// ============================
	// ========= METHODS ==========
	// ============================

	Goblin()
	{
		// Enemy Info
		name = "Goblin";
		hitPoints = roll(2, 6);
		armorClass = 13;
		hasShield = true;
		speed = 30;
		OA_AC = armorClass - (speed - 30)/5;
		expReward = 50;

		// Stats
		STR = 8;
		DEX = 14;
		CON = 10;
		INT = 10;
		WIS = 8;
		CHA = 8;

		// Stat Modifiers
		int modSTR = statMod(STR);
		int modDEX = statMod(DEX);
		int modCON = statMod(CON);
		int modINT = statMod(INT);
		int modWIS = statMod(WIS);
		int modCHA = statMod(CHA);
	};
	~Goblin();

	int attack() 
	{
		return roll(1, 6) + 2;
	}
	virtual int damage() = 0;
	virtual void move() = 0;
	virtual void idle() = 0;
	virtual bool canSeePlayer() = 0;
};

#endif