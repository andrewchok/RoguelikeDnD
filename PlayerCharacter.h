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
#include <time.h>
#include "Character.h"
#include "Helper.h"
#include <queue>


class PlayerCharacter : public Character
{
public:

	// ============================
	// ======== VARIABLES =========
	// ============================

	// Player Info
	std::string race = "";
	int level = 0;
	int proficiencyBonus = 0;
	std::string Language = "";
	std::string dndClass = "";
	std::string Equipment = "";
	std::string dmgRoll = "";
	int restDiceMaxCount = 1;
	int restDiceCurrentCount = 1;
	int restDiceType = 10;
	int rations = 5;

	bool isFighting = false;
	bool isGettingItem = false;

	int numOfEnemiesEngaged = 0;

	int floor = 1;
	int gold = 0;
	int exp = 0;
	int hunger = 500;

	std::queue<int> levelAdvancement = {};

	// ============================
	// ========= METHODS ==========
	// ============================

	PlayerCharacter() {};
	virtual ~PlayerCharacter() {};

	virtual int crit() = 0;
	virtual int attack(Character* enemy) = 0;
	virtual int damage() = 0;
	virtual void shortRest() = 0;
	virtual void longRest() = 0;
	virtual void showAbilities() = 0;
	virtual bool levelUp() = 0;

	bool fightCheck(char destination)
	{
		if (destination == 'J') return true;
		if (destination == 'V') return true;
		if (destination == 'K') return true;
		if (destination == 'C') return true;
		if (destination == 'G') return true;
		if (destination == 'S') return true;
		if (destination == 'Z') return true;
		if (destination == 'H') return true;
		if (destination == 'O') return true;
		if (destination == 'T') return true;
		if (destination == 'B') return true;
		if (destination == 'M') return true;
		if (destination == 'N') return true;
		if (destination == 'W') return true;

		return false;
	}

	bool movePlayer(Direction dir, char destination) 
	{
		if (fightCheck(destination))
		{
			isFighting = true;
			return false;
		}
		else {
			if (!(destination == '$' || destination == '&')) 
			{
				isGettingItem = true;
			}
			else isGettingItem = false;

			if (!(destination == '-' || destination == '|' || destination == ' '))
			{
				if (hunger > 0) this->hunger--;
				if (hunger <= 0) this->hitPoints--;
				switch (dir)
				{
				case up:
					this->location.y--;
					return true;
				case down:
					this->location.y++;
					return true;
				case left:
					this->location.x--;
					return true;
				case right:
					this->location.x++;
					return true;
				}
			}
			else return false;
		}
	};
};

#endif