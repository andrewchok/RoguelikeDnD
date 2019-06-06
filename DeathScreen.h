#pragma once
#ifndef DEATHSCREEN
#define DEATHSCREEN

#include <iostream>
#include <string>
#include <conio.h>
#include "KeyStrokes.h"
#include "PlayerCharacter.h"

class DeathScreen
{
public:
	DeathScreen() {};
	~DeathScreen() {};

	void drawDeathScreen()
	{
		system("CLS");
		std::cout <<
			"\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"--------------------------------------------------------------------------------\n"
			"--------------------------------------------------------------------------------\n"
			"--------------------------------------------------------------------------------\n"
			"                               YOU DIED.                                        \n"
			"--------------------------------------------------------------------------------\n"
			"--------------------------------------------------------------------------------\n"
			"--------------------------------------------------------------------------------\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"Press <space> to continue...\n";

		char wait = '~';
		while (wait != KEY_SPACE)
		{
			wait = _getch();
		}
	}

	void showStats(PlayerCharacter* player)
	{
		system("CLS");
		std::cout <<
			"\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"\n"
			"--------------------------------------------------------------------------------\n"
			"--------------------------------------------------------------------------------\n"
			"--------------------------------------------------------------------------------\n"
			"                               YOU DIED.                                        \n"
			"--------------------------------------------------------------------------------\n"
			"--------------------------------------------------------------------------------\n"
			"--------------------------------------------------------------------------------\n"
			"\n"
			"	Name: " + player->name + "\n"
			"	Level: " + std::to_string(player->level) + "\n"
			"	Experience points: " + std::to_string(player->exp) + "\n"
			"	Floor: " + std::to_string(player->floor) + "\n"
			"	Gold: " + std::to_string(player->gold) + "\n"
			"\n"
			"\n"
			"Press <space> to continue...\n";

		char wait = '~';
		while (wait != KEY_SPACE)
		{
			wait = _getch();
		}
	}
};


#endif