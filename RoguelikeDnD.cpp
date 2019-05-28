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
	ui[0] = 'F';
	ui[1] = 'l';
	ui[2] = 'o';
	ui[3] = 'o';
	ui[4] = 'r';
	ui[5] = ':';
	ui[6] = '1';
	ui[7] = ' ';
	ui[8] = ' ';
	ui[9] = ' ';

	// Hit Points (HP) [10 - 21] values [13 - 20]
	ui[10] = 'H';
	ui[11] = 'P';
	ui[12] = ':';
	ui[13] = '1';
	ui[14] = '0';
	ui[15] = '(';
	ui[16] = '1';
	ui[17] = '0';
	ui[18] = ')';
	ui[19] = ' ';
	ui[20] = ' ';

	// Armor Class (AC) [22 - 26] values [24 - 25]
	ui[21] = 'A';
	ui[22] = 'C';
	ui[23] = ':';
	ui[24] = '1';
	ui[25] = '0';
	ui[26] = ' ';

	// Attack Bonus (Atk) [27 - 34] values [31 - 33]
	ui[27] = 'A';
	ui[28] = 't';
	ui[29] = 'k';
	ui[30] = ':';
	ui[31] = '+';
	ui[32] = '2';
	ui[33] = ' ';
	ui[34] = ' ';

	// Damage Roll (Dmg) [35 - 44] values [39 - 43]
	ui[35] = 'D';
	ui[36] = 'm';
	ui[37] = 'g';
	ui[38] = ':';
	ui[39] = '1';
	ui[40] = 'd';
	ui[41] = '6';
	ui[42] = ' ';
	ui[43] = ' ';
	ui[44] = ' ';

	// Gold [45 - 55] values [50 - 54]
	// for this Roguelike Gold will be equivalent to Silver Pieces
	ui[45] = 'G';
	ui[46] = 'o';
	ui[47] = 'l';
	ui[48] = 'd';
	ui[49] = ':';
	ui[50] = '0';
	ui[51] = ' ';
	ui[52] = ' ';
	ui[53] = ' ';
	ui[54] = ' ';
	ui[55] = ' ';

	// Experience Points (Exp) [56 - 66] values [60 - 65]
	ui[56] = 'E';
	ui[57] = 'x';
	ui[58] = 'p';
	ui[59] = ':';
	ui[60] = '0';
	ui[61] = ' ';
	ui[62] = ' ';
	ui[63] = ' ';
	ui[64] = ' ';
	ui[65] = ' ';
	ui[66] = ' ';

	// Hunger [67 - 77] values [74 - 76]
	// for this Rogue like having Hunger management increases the difficulty 
	ui[67] = 'H';
	ui[68] = 'u';
	ui[69] = 'n';
	ui[70] = 'g';
	ui[71] = 'e';
	ui[72] = 'r';
	ui[73] = ':';
	ui[74] = '1';
	ui[75] = '0';
	ui[76] = '0';
	
	// new line char
	ui[77] = '\n';

	uiStr = ui;
}

void updateUI()
{
	// Floor [6 - 8]

	// Hit Points (HP) values [13 - 20]

	// Armor Class (AC) values [24 - 25]

	// Attack Bonus (Atk) values [31 - 33]

	// Damage Roll (Dmg) values [39 - 43]

	// Gold values [50 - 54]

	// Experience Points (Exp) values [60 - 65]

	// Hunger values [74 - 76]
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
	gameStr = message + mapStr + uiStr + specialMsg;
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