#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <conio.h>
#include "KeyStrokes.h"
#include "Units.h"

// Game dimension constants
const int GAME_WIDTH = 80; 
const int GAME_HEIGHT = 25;
const int GAME_MAP_HEIGHT = 23;

// Global Variables
// GAME_WIDTH + 1 (for \n)
int input = -1;
char message[GAME_WIDTH + 1] = { 0 };
char Map[GAME_WIDTH + 1][GAME_MAP_HEIGHT] = { 0 };
char expMap[GAME_WIDTH + 1][GAME_MAP_HEIGHT] = { 0 };	// exp -> explored
char ui[GAME_WIDTH + 1] = { 0 };						// ui -> user interface
char specialMsg[GAME_WIDTH + 1] = { 0 };
std::string messageStr = "";
std::string mapStr = "";
std::string uiStr = "";
std::string specialMsgStr = "";
std::string gameStr = "";

Fighter* player = new Fighter();

// Method Declarations
void clearMessage();
void updateMessage();
bool createRoom();
void clearExpMap();
void updateExpMap();
void makeExpMap();
void initUI();
void updateUI();
void updateSpecialMsg();
void drawGame();
bool placePlayer();
void updatePlayer();

void clearMessage()
{
	message[0] = '\n';
	message[1] = '\0';
}

void updateMessage()
{
	// clear existing message and make message here 
}

bool createRoom()
{
	// location of top left corner of room
	int x_loc = 0;
	int y_loc = 0;

	// size of room
	int x_size = 10;
	int y_size = 8;

	for (int y = y_loc; y < y_loc + y_size; y++)
	{
		for (int x = x_loc; x < (x_loc + x_size) && y == y_loc; x++)
		{
			expMap[x][y] = '-';
		}

		for (int x = x_loc; x < (x_loc + x_size) && y != y_loc && y != (y_size - 1); x++)
		{
			if (x == x_loc || x == (x_loc + x_size - 1)) expMap[x][y] = '|';
			else expMap[x][y] = '.';
		}

		for (int x = x_loc; x < (x_loc + x_size) && y == (y_loc + y_size - 1); x++)
		{
			expMap[x][y] = '-';
		}
	}

	return true;
}

void clearExpMap()
{
	for (int y = 0; y < GAME_MAP_HEIGHT; y++)
	{
		for (int x = 0; x < GAME_WIDTH; x++)
		{
			expMap[x][y] = ' ';
		}
		expMap[GAME_WIDTH][y] = '\n';
	}
}

void updateExpMap()
{
	createRoom();
}

void makeExpMap()
{
	mapStr = "";
	for (int y = 0; y < GAME_MAP_HEIGHT; y++)
	{
		for (int x = 0; x < GAME_WIDTH + 1; x++)
		{
			mapStr += expMap[x][y];
		}
	}
}

void initUI()
{
	// Floor [0 - 9] values [6 - 8]
	// ui[0 - 9] = "Floor:999 "

	// Hit Points (HP) [10 - 21] values [13 - 20]
	// ui[10 - 21] = "HP:999(999) "

	// Armor Class (AC) [22 - 27] values [25 - 26]
	// ui[22 - 27] = "AC:99 "

	// Attack Bonus (Atk) [28 - 35] values [32 - 34]
	// ui[28 - 35] = "Atk:+99 "

	// Damage Roll (Dmg) [36 - 45] values [40 - 44]
	// ui[36 - 45] = "Dmg:99d20 "

	// Gold [46 - 56] values [51 - 55]
	// for this Roguelike Gold will be equivalent to Silver Pieces
	// ui[46 - 56] = "Gold:99999 "

	// Experience Points (Exp) [57 - 67] values [61 - 66]
	// ui[57 - 67] = "Exp:999999 "

	// Hunger [68 - 78] values [75 - 77]
	// for this Rogue like having Hunger management increases the difficulty 
	// ui[68 - 78] = "Hunger:999\n"

	uiStr = "Floor:999 HP:999(999) AC:99 Atk:+99 Dmg:99d99 Gold:99999 Exp:999999 Hunger:999\n";

	specialMsgStr = uiStr;
}

void updateUI()
{
	std::string str = "";
	// Floor [6 - 8]
	str = std::to_string(player->floor);
	str.resize(4);
	specialMsgStr.replace(6, 4, str);
	// Hit Points (HP) values [13 - 20]
	str = std::to_string(player->hitPoints) + "(" + std::to_string(player->maxHitPoints) + ")";
	str.resize(8);
	specialMsgStr.replace(13, 8, str);
	// Armor Class (AC) values [25 - 26]
	if(player->hasShield) str = std::to_string(player->armorClass + 2);
	else str = std::to_string(player->armorClass);
	str.resize(3);
	specialMsgStr.replace(25, 3, str);
	// Attack Bonus (Atk) values [32 - 34]
	str = "+" + std::to_string(player->proficiencyBonus + player->modSTR);
	str.resize(4);
	specialMsgStr.replace(32, 4, str);
	// Damage Roll (Dmg) values [40 - 44]
	str = player->dmgRoll;
	str.resize(6);
	specialMsgStr.replace(40, 6, str);
	// Gold values [51 - 55]
	str = std::to_string(player->gold);
	str.resize(6);
	specialMsgStr.replace(51, 6, str);
	// Experience Points (Exp) values [61 - 66]
	str = std::to_string(player->exp);
	str.resize(7);
	specialMsgStr.replace(61, 7, str);
	// Hunger values [75 - 77]
	str = std::to_string(player->hunger);
	str.resize(3);
	specialMsgStr.replace(75, 3, str);
}

void updateSpecialMsg()
{
	// write code to show special msg
	specialMsg[0] = 's';
	specialMsg[1] = 'p';
	specialMsg[2] = '\n';
	specialMsg[3] = '\0';
}

void drawGame()
{
	gameStr = "";
	gameStr = message + mapStr + uiStr + specialMsgStr;
	std::cout << gameStr;
}

bool placePlayer()
{
	// choose random room
	// place randomly in that room but not on top of any items

	int x_pos = 3;
	int y_pos = 3;
		
	if (player->setLocation(x_pos, y_pos))
	{
		expMap[x_pos][y_pos] = '@';

		return true;
	}

	return false;
}

void updatePlayer()
{
	expMap[player->x_pos][player->y_pos] = '@';
}

int main()
{
	bool newLvl = true;
	clearMessage();
	clearExpMap();
	initUI();

	while (true)
	{
		updateMessage();
		updateExpMap();
		if (newLvl)
		{
			placePlayer();
			newLvl = false;
		}
		else updatePlayer();
		makeExpMap();
		updateUI();
		updateSpecialMsg();
		

		system("CLS");
		drawGame();

		input = _getch();

		if (input == KEY_BRANCH_0 || input == KEY_BRANCH_244)
		{
			input = _getch();

			//quit game funciton
			if (input == KEY_F12)
			{
				input = _getch();
				if (input == KEY_q) break;
				if (input == KEY_s); //write save game function
				if (input == KEY_l); //write load game function
			}

			// Arrow key movement
			switch (input)
			{
			case KEY_ARROW_UP : 
				if (expMap[player->x_pos][player->y_pos - 1] != '-') player->y_pos--;
				break;
			case KEY_ARROW_DOWN : 
				if (expMap[player->x_pos][player->y_pos + 1] != '-') player->y_pos++;
				break;
			case KEY_ARROW_LEFT : 
				if (expMap[player->x_pos - 1][player->y_pos] != '|') player->x_pos--;
				break;
			case KEY_ARROW_RIGHT : 
				if (expMap[player->x_pos + 1][player->y_pos] != '|') player->x_pos++;
				break;
			}

		}
	}

	return 0;
}