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
#ifndef PLAYERCHARACTER
#define PLAYERCHARACTER
#include <string>


class PlayerCharacter
{
public:

	// ============================
	// ======== VARIABLES =========
	// ============================

	std::string race = "Mountain Dwarf";

	int proficiencyBonus = 2;

	int hitPoints = 13;

	int armorClass = 18;

	int speed = 25;
	int OA_AC = armorClass - 1;

	std::string Language = "Common and Dwarvish";

	std::string dndClass = "Fighter(Champion Path)";

	int STR = 17;
	int DEX = 10;
	int CON = 16;
	int INT = 8;
	int WIS = 13;
	int CHA = 12;

	std::string Equipment = "a. Battleaxe : 1d8 slashing | Versatile(1d10)\nb. 2 Handaxes : 1d6 slashing | Light; Thrown(range 4/12)";

	int x_pos = -1;
	int y_pos = -1;

	// ============================
	// ========= METHODS ==========
	// ============================

	PlayerCharacter();
	~PlayerCharacter();


};

#endif