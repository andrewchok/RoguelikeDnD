#pragma once
#ifndef CHARACTER
#define CHARACTER
#include <string>
#include <time.h>

class Character
{
public:

	// ============================
	// ======== VARIABLES =========
	// ============================

	// Character Info
	std::string name = "";
	int hitPoints = 0;
	int armorClass = 0;
	bool hasShield = false;
	int speed = 0;
	int OA_AC = armorClass - 1;

	// Stats
	int STR = 0;
	int DEX = 0;
	int CON = 0;
	int INT = 0;
	int WIS = 0;
	int CHA = 0;

	// Stat Modifiers
	int modSTR = -1;
	int modDEX = 2;
	int modCON = 0;
	int modINT = 0;
	int modWIS = -1;
	int modCHA = -1;

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
		srand(time(NULL));

		for (int i = 0; i < num; i++)
		{
			result += rand() % value + 1;
		}
		return result;
	};

	int roll20()
	{
		int result = 0;

		srand(time(NULL));
		result += rand() % 20 + 1;

		if (result == 20); // nat 20
		if (result == 1); // nat 1

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

	virtual int attack() = 0;
	virtual int damage() = 0;
};

#endif