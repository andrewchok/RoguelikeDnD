#pragma once
#ifndef MERROW
#define MERROW
#include <string>
#include "EnemyCharacter.h"

class Merrow : public EnemyCharacter
{
public:

	// ============================
	// ======== VARIABLES =========
	// ============================

	// ============================
	// ========= METHODS ==========
	// ============================

	Merrow()
	{
		// Enemy Info
		token = 'M';
		name = "Merrow";
		hitPoints = roll(6, 10) + 12;
		armorClass = 13;
		hasShield = false;
		speed = 40;
		OA_AC = armorClass - (speed - 30) / 5;
		expReward = 450;

		hitModifier = 6;

		// Stats
		STR = 18;
		DEX = 10;
		CON = 15;
		INT = 8;
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
	~Merrow() {};

	int crit()
	{
		return roll(2, 6);
	};

	int attack(Character* player)
	{
		if (this->hitPoints <= 0) return 0;

		int dmgDealtToPlayer = 0;

		int roll = roll20();
		roll = (roll == NAT_20) ? NAT_20 : roll + hitModifier;

		// player does damage if roll >= to enemy AC
		if (roll >= (player->hasShield ? player->armorClass + SHIELD_AC : player->armorClass))
		{
			dmgDealtToPlayer = (roll == NAT_20) ? this->damage() + this->crit() : this->damage();
		}

		roll = (roll == NAT_20) ? NAT_20 : roll + hitModifier;

		// player does damage if roll >= to enemy AC
		if (roll >= (player->hasShield ? player->armorClass + SHIELD_AC : player->armorClass))
		{
			dmgDealtToPlayer += (roll == NAT_20) ? (this->roll(2, 8)) + 4 : (this->roll(1, 8)) + 4;
		}

		player->hitPoints -= dmgDealtToPlayer;

		return dmgDealtToPlayer;
	};

	int damage()
	{
		return roll(2, 6) + 4;
	};
};

#endif