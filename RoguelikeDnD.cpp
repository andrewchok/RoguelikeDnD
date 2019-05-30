#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <conio.h>
#include "KeyStrokes.h"
#include "Units.h"
#include "Enums.h"

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
//char ui[GAME_WIDTH + 1] = { 0 };						// ui -> user interface
char specialMsg[GAME_WIDTH + 1] = { 0 };
std::string messageStr = "";
std::string mapStr = "";
std::string uiStr = "";
std::string specialMsgStr = "";
std::string gameStr = "";
char destination = ' ';
bool isFighting = false;
int playerHitRoll = 0;
int enemyHitRoll[10] = { 0 };
bool wasPlayerHit = false;
bool wasEnemyHit = false;
int dmgDealtToPlayer = 0;
int dmgDealtToEnemy = 0;
bool newLvl = true;

PlayerCharacter* player = new Fighter();
EnemyCharacter* enemy[10] = { 0 };

// Method Declarations
void drawDeathScreen();

void clearMessage();
void updateMessage();

bool createRoom();
bool spawnEnemy();
void clearExpMap();
void updateExpMap();
void makeExpMap();

void initUI();
void updateUI();
void updateSpecialMsg();

void drawGame();

bool placePlayer();
void updatePlayer();
void updateEnemy();


// Method Definitions
void drawDeathScreen()
{
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
		"\n";
}

void clearMessage()
{
	messageStr = "\n";
}

void updateMessage()
{
	// clear existing message and make message here 
	
	if (isFighting)
	{
		//bool wasPlayerHit 
		//bool wasEnemyHit
		//int dmgDealtToPlayer 
		//int dmgDealtToEnemy 
		messageStr = "";
		messageStr = "You swung and ";
		if (wasEnemyHit)
		{
			if (playerHitRoll == NAT_20) messageStr += "crit ";
			else messageStr += "hit ";
			
			messageStr += enemy[0]->name + " for " + std::to_string(dmgDealtToEnemy) + " damage. ";
		}
		else messageStr += "missed! ";

		messageStr += enemy[0]->name + " swung and ";
		if (wasPlayerHit)
		{
			if (enemyHitRoll[0] == NAT_20) messageStr += "crit ";
			else messageStr += "hit ";

			messageStr += "you for " + std::to_string(dmgDealtToPlayer) + " damage. ";
		}
		else messageStr += "missed! ";


	}


	messageStr += "\n";
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

bool spawnEnemy()
{
	// randomly check for how many enemies to spawn based on floor
	// spawn said enemy
	// choose random room
	// place randomly in that room but not on top of any items

	int x_pos = 5;
	int y_pos = 5;

	enemy[0] = new Goblin();

	if (enemy[0]->setLocation(x_pos, y_pos))
	{
		expMap[x_pos][y_pos] = 'G';

		return true;
	}

	return false;
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
	createRoom(); // to be moved to actuall map and not explored map
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
}

void updateUI()
{
	std::string str = "";
	// Floor [6 - 8]
	str = std::to_string(player->floor);
	str.resize(4);
	uiStr.replace(6, 4, str);
	// Hit Points (HP) values [13 - 20]
	str = std::to_string(player->hitPoints) + "(" + std::to_string(player->maxHitPoints) + ")";
	str.resize(8);
	uiStr.replace(13, 8, str);
	// Armor Class (AC) values [25 - 26]
	if(player->hasShield) str = std::to_string(player->armorClass + 2);
	else str = std::to_string(player->armorClass);
	str.resize(3);
	uiStr.replace(25, 3, str);
	// Attack Bonus (Atk) values [32 - 34]
	str = "+" + std::to_string(player->proficiencyBonus + player->modSTR);
	str.resize(4);
	uiStr.replace(32, 4, str);
	// Damage Roll (Dmg) values [40 - 44]
	str = player->dmgRoll;
	str.resize(6);
	uiStr.replace(40, 6, str);
	// Gold values [51 - 55]
	str = std::to_string(player->gold);
	str.resize(6);
	uiStr.replace(51, 6, str);
	// Experience Points (Exp) values [61 - 66]
	str = std::to_string(player->exp);
	str.resize(7);
	uiStr.replace(61, 7, str);
	// Hunger values [75 - 77]
	str = std::to_string(player->hunger);
	str.resize(3);
	uiStr.replace(75, 3, str);
}

void updateSpecialMsg()
{
	// write code to show special msg
	specialMsgStr = "";
	specialMsgStr = "Name:" + player->name + "     Level:" + std::to_string(player->level) + "    Class:" + player->dndClass + "\n";
}

void drawGame()
{
	gameStr = "";
	gameStr = messageStr + mapStr + uiStr + specialMsgStr;
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

void updateEnemy()
{
	if (enemy[0] != nullptr)
	{
		if (enemy[0]->hitPoints > 0) expMap[enemy[0]->x_pos][enemy[0]->y_pos] = 'G';
		else
		{
			delete enemy[0];
			enemy[0] = nullptr;
		}
	}
}


// Main function

int main()
{
	clearMessage();
	clearExpMap();
	initUI();
	spawnEnemy();

	while (true)
	{
		if (player->hitPoints <= 0)
		{
			system("CLS");
			drawDeathScreen();
			break;
		}

		updateExpMap();

		if (newLvl)
		{
			placePlayer();
			newLvl = false;
		}
		else updatePlayer();
		updateEnemy();

		makeExpMap();
		updateUI();
		updateSpecialMsg();
		

		system("CLS");
		drawGame();

		input = _getch();

		clearMessage();

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
				//if (expMap[player->x_pos][player->y_pos - 1] != '-') player->y_pos--;
				destination = expMap[player->x_pos][player->y_pos - 1];
				isFighting = !player->movePlayer(MOVE_UP, destination);
				break;
			case KEY_ARROW_DOWN : 
				//if (expMap[player->x_pos][player->y_pos + 1] != '-') player->y_pos++;
				destination = expMap[player->x_pos][player->y_pos + 1];
				isFighting = !player->movePlayer(MOVE_DOWN, destination);
				break;
			case KEY_ARROW_LEFT : 
				//if (expMap[player->x_pos - 1][player->y_pos] != '|') player->x_pos--;
				destination = expMap[player->x_pos - 1][player->y_pos];
				isFighting = !player->movePlayer(MOVE_LEFT, destination);
				break;
			case KEY_ARROW_RIGHT : 
				//if (expMap[player->x_pos + 1][player->y_pos] != '|') player->x_pos++;
				destination = expMap[player->x_pos + 1][player->y_pos];
				isFighting = !player->movePlayer(MOVE_RIGHT, destination);
				break;
			}

			if (isFighting)
			{
				if (destination == 'G')
				{
					if (enemy[0]->hasShield)
					{
						playerHitRoll = player->attack();
						wasEnemyHit = (playerHitRoll >= (enemy[0]->armorClass + ShieldAC)); //player does damage
					}
					else
					{
						playerHitRoll = player->attack();
						wasEnemyHit = (playerHitRoll > enemy[0]->armorClass); //player does damage
					}

					if (wasEnemyHit) // player to enemy
					{
						if (playerHitRoll == NAT_20)
						{
							dmgDealtToEnemy = player->crit() + player->damage();
						}
						else dmgDealtToEnemy = player->damage();

						enemy[0]->hitPoints -= dmgDealtToEnemy;
					}
					else dmgDealtToEnemy = 0;

					if (player->hasShield)
					{
						enemyHitRoll[0] = enemy[0]->attack();
						wasPlayerHit = (enemyHitRoll[0] >= (player->armorClass + ShieldAC)); //enemy does damage
					}
					else
					{
						enemyHitRoll[0] = enemy[0]->attack();
						wasPlayerHit = (enemyHitRoll[0] > player->armorClass); //enemy does damage
					}

					if (wasPlayerHit) // enemy to player
					{
						if (enemyHitRoll[0] == NAT_20)
						{
							dmgDealtToPlayer = enemy[0]->crit() + enemy[0]->damage();
						}
						else dmgDealtToPlayer = enemy[0]->damage();

						player->hitPoints -= dmgDealtToPlayer;
					}
					else dmgDealtToPlayer = 0;

					updateMessage();
				}
			}

		}
	}

	return 0;
}