/*
D&D PHB Quick Build Example: Bruenor

Race: Mountain Dwarf ( +2 STR, +2 CON)

Proficiency Bonus : +2 (level 1)

Hit Points : 13

Armor Class : 18 (with 16 chainmail and +2 from shield)

Speed : 25ft (for this Roguelike for each 5ft speed difference from 30ft it +/- 1 from AC for Oppurtunity Attacks)
OA AC : 17

Language : Common and Dwarvish

Class : Fighter (Champion Path)

STR : 15 + 2 = 17 (+3)
DEX : 10 + 0 = 10 (+0)
CON : 14 + 2 = 16 (+3)
INT :  8 + 0 =  8 (-1)
WIS : 13 + 0 = 13 (+1)
CHA : 12 + 0 = 12 (+1)

Equipment:
- Battleaxe		1d8 slashing | Versatile (1d10)
- 2 Handaxes	1d6 slashing | Light; Thrown (range 20ft/60ft)[4/12] (for this roguelike every 5ft is one tile)
*/
#pragma once
#ifndef FIGHTER
#define FIGHTER
#include <string>
#include <time.h>
#include "PlayerCharacter.h"

class Fighter : public PlayerCharacter
{
public:

	// ============================
	// ======== VARIABLES =========
	// ============================

	// ============================
	// ========= METHODS ==========
	// ============================

	Fighter()
	{
		// Player Info
		token = '@';
		name = "Bruenor";
		level = 1;
		hitPoints = 13;
		maxHitPoints = 13;
		armorClass = 16;
		hasShield = true;
		speed = 25;
		OA_AC = armorClass - (speed - 30) / 5;
		race = "Mountain Dwarf";
		proficiencyBonus = 2;
		Language = "Common and Dwarvish";
		dndClass = "Fighter";
		Equipment = "a. Battleaxe : 1d8 slashing | Versatile(1d10)\nb. 2 Handaxes : 1d6 slashing | Light; Thrown(range 4/12)";
		dmgRoll = "1d8";

		restDiceMaxCount = 1;
		restDiceCurrentCount = 1;
		restDiceType = 10;

		levelAdvancement.push(300); // lvl 2
		levelAdvancement.push(900); // lvl 3
		levelAdvancement.push(2700); // lvl 4
		levelAdvancement.push(6500); // lvl 5
		levelAdvancement.push(14000); // lvl 6
		levelAdvancement.push(23000); // lvl 7
		levelAdvancement.push(34000); // lvl 8
		levelAdvancement.push(48000); // lvl 9
		levelAdvancement.push(64000); // lvl 10
		levelAdvancement.push(85000); // lvl 11
		levelAdvancement.push(100000); // lvl 12
		levelAdvancement.push(120000); // lvl 13
		levelAdvancement.push(140000); // lvl 14
		levelAdvancement.push(165000); // lvl 15
		levelAdvancement.push(195000); // lvl 16
		levelAdvancement.push(225000); // lvl 17
		levelAdvancement.push(265000); // lvl 18
		levelAdvancement.push(305000); // lvl 19
		levelAdvancement.push(355000); // lvl 20

		// Stats
		STR = 17;
		DEX = 10;
		CON = 16;
		INT = 8;
		WIS = 13;
		CHA = 12;

		// Stat Modifiers
		modSTR = statMod(STR);
		modDEX = statMod(DEX);
		modCON = statMod(CON);
		modINT = statMod(INT);
		modWIS = statMod(WIS);
		modCHA = statMod(CHA);
	};
	~Fighter() {};

	int crit()
	{
		return roll(1, 8);
	};

	int improvedCritRoll20()
	{
		int result = 0;

		srand(unsigned(time(NULL) * 7 * rand()));
		result += rand() % 20 + 1;

		if (result == 20 || result == 19) return NAT_20; // nat 20
		if (result == 1) return NAT_1; // nat 1

		return result;
	};

	int attack(Character* enemy)
	{
		int dmgDealtToEnemy = 0;

		int roll = roll20();
		if(this->level >= 3) roll = improvedCritRoll20();
		roll = (roll == NAT_20) ? NAT_20 : roll + proficiencyBonus + modSTR;

		// player does damage if roll >= to enemy AC
		if (roll >= (enemy->hasShield ? enemy->armorClass + ShieldAC : enemy->armorClass))
		{
			dmgDealtToEnemy = (roll == NAT_20) ? this->damage() + this->crit() : this->damage();
			enemy->hitPoints -= dmgDealtToEnemy;
		}

		return dmgDealtToEnemy;
	};

	int damage()
	{
		return roll(1, 8) + modSTR;
	};

	void shortRest() {};
	void longRest() {};
	void showAbilities() {};
	void levelUp() 
	{
		int hpIncrease = 0;
		int tempModCON = 0;

		if (this->exp >= levelAdvancement.front())
		{
			switch (levelAdvancement.front())
			{
				case (300): // level 2
					this->level = 2;

					//gain action surge (1 use)
					break;
				case (900): // level 3
					this->level = 3;

					this->dndClass = "Fighter(Champion)";
					break;
				case (2700): // level 4
					this->level = 4;
					
					this->STR++; 
					modSTR = statMod(STR);
					this->CON++; 
					tempModCON = modCON;
					modCON = statMod(CON);

					if (modCON > tempModCON)
					{
						this->maxHitPoints += this->level - 1;
						this->hitPoints += this->level - 1;
					}
					
					break;
				case (6500): // level 5
					this->level = 5;

					this->proficiencyBonus = 3;

					// add Extra Attack
					break;
				case (14000):
					break;
				case (23000):
					break;
				case (34000):
					break;
				case (48000):
					break;
				case (64000):
					break;
				case (85000):
					break;
				case (100000):
					break;
				case (120000):
					break;
				case (140000):
					break;
				case (165000):
					break;
				case (195000):
					break;
				case (225000):
					break;
				case (265000):
					break;
				case (305000):
					break;
				case (355000):
					break;
			}

			hpIncrease = roll(1, 10) + this->modCON;
			this->maxHitPoints += hpIncrease;
			this->hitPoints += hpIncrease;
			this->restDiceMaxCount++;
			this->restDiceCurrentCount++;

			levelAdvancement.pop();
		}
		
	};

};

#endif