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
		name = "Bruenor";
		level = 1;
		hitPoints = 999;//13;
		maxHitPoints = 13;
		armorClass = 16;
		hasShield = true;
		speed = 25;
		OA_AC = armorClass - (speed - 30) / 5;
		race = "Mountain Dwarf";
		proficiencyBonus = 2;
		Language = "Common and Dwarvish";
		dndClass = "Fighter(Champion Path)";
		Equipment = "a. Battleaxe : 1d8 slashing | Versatile(1d10)\nb. 2 Handaxes : 1d6 slashing | Light; Thrown(range 4/12)";
		dmgRoll = "1d8";

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

	int attack()
	{
		int roll = roll20();
		return (roll == NAT_20) ? NAT_20 : roll + proficiencyBonus + modSTR;
	};
	
	int damage()
	{
		return roll(1, 8) + modSTR;
	};

};

#endif