#pragma once
#ifndef CHARACTER
#define CHARACTER
#include <string>
#include <time.h>
#include "GameMap.h"

#define NAT_20 99
#define NAT_1 -99
#define ShieldAC 2

class Character
{
public:

	// ============================
	// ======== VARIABLES =========
	// ============================

	// Character Info
	char token = '?';
	std::string name = "";
	int hitPoints = 0;
	int maxHitPoints = 0;
	int armorClass = 0;
	bool hasShield = false;
	int speed = 0;
	int OA_AC = armorClass - 1;

	// Stats
	int STR = 999;
	int DEX = 999;
	int CON = 999;
	int INT = 999;
	int WIS = 999;
	int CHA = 999;

	// Stat Modifiers
	int modSTR = 999;
	int modDEX = 999;
	int modCON = 999;
	int modINT = 999;
	int modWIS = 999;
	int modCHA = 999;

	int x_pos = -1;
	int y_pos = -1;

	// ============================
	// ========= METHODS ==========
	// ============================

	Character() {};
	virtual ~Character() {};

	int roll(int num, int value)
	{
		int result = 0;
		srand( unsigned(time(NULL) * 13 * rand()) );

		for (int i = 0; i < num; i++)
		{
			result += rand() % value + 1;
		}
		return result;
	};

	int roll20()
	{
		int result = 0;

		srand(unsigned(time(NULL) * 7 * rand()) );
		result += rand() % 20 + 1;

		if (result == 20) return NAT_20; // nat 20
		if (result == 1) return NAT_1; // nat 1

		return result;
	};

	int statMod(int stat)
	{
		double result = ((double)stat - 10) / 2;
		return (int)floor(result);
	};

	bool setLocation(int x_pos, int y_pos)
	{
		if (x_pos > 0 && x_pos < 80 && y_pos > 0 && y_pos < 23)
		{
			this->x_pos = x_pos;
			this->y_pos = y_pos;
			return true;
		}
		return false;
	};

	virtual int crit() = 0;
	virtual int attack() = 0;
	virtual int damage() = 0;
};

#endif