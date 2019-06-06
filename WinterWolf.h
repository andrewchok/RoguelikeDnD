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

		hitModifier = 6;
		
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
		return roll(2, 6);
	};

	int damage()
	{
		return roll(2, 6) + 4;
	};

	int attack(Character* player)
	{
		if (this->hitPoints <= 0) return 0;

		int dmgDealtToPlayer = 0;

		int diceRoll = roll20();
		diceRoll = (diceRoll == NAT_20) ? NAT_20 : diceRoll + hitModifier;

		int advRoll = roll20();
		if (advRoll > diceRoll) diceRoll = advRoll;

		// coldBreath
		if (roll(1, 6) >= 5)
		{
			dmgDealtToPlayer = roll(4, 8);
			if (roll20() + player->modDEX >= 12) dmgDealtToPlayer /= 2;
		}
		// player does damage if roll >= to enemy AC
		else if (diceRoll >= (player->hasShield ? player->armorClass + ShieldAC : player->armorClass))
		{
			dmgDealtToPlayer = (diceRoll == NAT_20) ? this->damage() + this->crit() : this->damage();
		}

		player->hitPoints -= dmgDealtToPlayer;

		return dmgDealtToPlayer;
	};
};

#endif