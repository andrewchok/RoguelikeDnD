#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <conio.h>
#include "KeyStrokes.h"
#include "Units.h"
#include "Enums.h"
#include "GameMap.h"
#include "PlayerInfo.h"
#include "StartScreen.h"
#include "DeathScreen.h"

// Global Variables
// GAME_WIDTH + 1 (for \n)
int input = -1;
char specialMsg[GAME_WIDTH + 1] = { 0 };
std::string messageStr = "";
std::string mapStr = "";
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

std::array<int, 2> stairs_loc = { 0, 0 };

StartScreen* startScreen = new StartScreen();
DeathScreen* deathScreen = new DeathScreen();

PlayerCharacter* player = new Fighter();
EnemyCharacter* enemy[10] = { 0 };

GameMap* gameMap = new GameMap();
PlayerInfo* ui = new PlayerInfo(player);

// Method Declarations
int randomNumber(int min, int max);

void clearMessage();
void updateMessage();

void updateSpecialMsg();

void drawGame();

bool placePlayer();
void updatePlayer();

bool placeStairs();
void updateStairs();

bool spawnEnemy();
void updateEnemy();


// Method Definitions

int randomNumber(int min, int max)
{
	srand(unsigned(time(NULL) * 11 * rand()));
	int value = (rand() % (max - min + 1)) + min;
	return value;
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

void updateSpecialMsg()
{
	// write code to show special msg
	specialMsgStr = "";
	specialMsgStr = "Name:" + player->name + "     Level:" + std::to_string(player->level) + "    Class:" + player->dndClass + "\n";
}

void drawGame()
{
	gameStr = "";
	gameStr = messageStr + gameMap->mapStr + ui->uiStr + specialMsgStr;
	std::cout << gameStr;
}

bool placePlayer()
{
	// choose random room
	// place randomly in that room but not on top of any items
	int x_start = gameMap->roomList.front()->x_start;
	int y_start = gameMap->roomList.front()->y_start;

	int x_size = gameMap->roomList.front()->x_size;
	int y_size = gameMap->roomList.front()->y_size;

	int x_pos = randomNumber(x_start + 1, x_start + x_size - 2);
	int y_pos = randomNumber(y_start + 1, y_start + y_size - 2);
		
	if (player->setLocation(x_pos, y_pos))
	{
		gameMap->expMap[x_pos][y_pos] = '@';

		return true;
	}

	return false;
}

void updatePlayer()
{
	gameMap->expMap[player->x_pos][player->y_pos] = '@';
	player->levelUp();
}

bool placeStairs()
{
	// choose random room
	// place randomly in that room but not on top of any items
	int x_start = gameMap->roomList[2]->x_start;
	int y_start = gameMap->roomList[2]->y_start;

	int x_size = gameMap->roomList[2]->x_size;
	int y_size = gameMap->roomList[2]->y_size;

	int x_pos = randomNumber(x_start + 1, x_start + x_size - 2);
	int y_pos = randomNumber(y_start + 1, y_start + y_size - 2);

	if (gameMap->map[x_pos][y_pos] == '.')
	{
		gameMap->map[x_pos][y_pos] = '%';
		stairs_loc = { x_pos, y_pos };
		return true;
	}

	return false;
}

void updateStairs()
{
	gameMap->map[stairs_loc[0]][stairs_loc[1]] = '%';
}

bool spawnEnemy()
{
	// randomly check for how many enemies to spawn based on floor
	// spawn said enemy
	// choose random room
	// place randomly in that room but not on top of any items

	int x_pos = 5;
	int y_pos = 5;

	//for (int i = 0; i < enemyCount; i++)
	//{
	//	map[x_pos][y_pos] = 'G';//enemy[i];
	//}
	enemy[0] = new Goblin();

	if (enemy[0]->setLocation(x_pos, y_pos))
	{
		gameMap->expMap[x_pos][y_pos] = 'G';

		return true;
	}


	return false;
}

void updateEnemy()
{
	if (enemy[0] != nullptr)
	{
		if (enemy[0]->hitPoints > 0) gameMap->expMap[enemy[0]->x_pos][enemy[0]->y_pos] = 'G';
		else
		{
			player->exp += enemy[0]->expReward;
			delete enemy[0];
			enemy[0] = nullptr;
		}
	}
}


// Main function

int main()
{
	while (true)
	{
		startScreen->drawStartScreen();
		if (startScreen->playerName == "quit") break;
		player->name = startScreen->playerName;

		clearMessage();

		while (true)
		{
			if (player->hitPoints <= 0)
			{
				deathScreen->drawDeathScreen();
				break;
			}
			
			if (newLvl)
			{
				gameMap->createNewMap();
				placeStairs();
				placePlayer();
				gameMap->explore(player->x_pos, player->y_pos);
				gameMap->refreshExpMap();

				updatePlayer();
				spawnEnemy();
				newLvl = false;
			}
			else
			{
				gameMap->explore(player->x_pos, player->y_pos);
				gameMap->refreshExpMap();
				//updateStairs();
				updatePlayer();
			}
			updateEnemy();


			gameMap->makeExpMap();
			ui->updateUI();
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
				case KEY_ARROW_UP:
					destination = gameMap->map[player->x_pos][player->y_pos - 1];
					isFighting = !player->movePlayer(MOVE_UP, destination);
					break;
				case KEY_ARROW_DOWN:
					destination = gameMap->map[player->x_pos][player->y_pos + 1];
					isFighting = !player->movePlayer(MOVE_DOWN, destination);
					break;
				case KEY_ARROW_LEFT:
					destination = gameMap->map[player->x_pos - 1][player->y_pos];
					isFighting = !player->movePlayer(MOVE_LEFT, destination);
					break;
				case KEY_ARROW_RIGHT:
					destination = gameMap->map[player->x_pos + 1][player->y_pos];
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
			if (input == KEY_e)
			{
				if (player->x_pos == stairs_loc[0] && player->y_pos == stairs_loc[1])
				{
					newLvl = true;
					player->floor++;
				}
			}
		}
	}

	return 0;
}