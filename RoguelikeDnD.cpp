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
struct Destination
{
	char token;
	int x, y;
};

Destination destination;
bool isFighting = false;
int playerHitRoll = 0;
int enemyHitRoll[10] = { 0 };
bool wasPlayerHit = false;
bool wasEnemyHit = false;
int dmgDealtToPlayer = 0;
int dmgDealtToEnemy = 0;
bool newLvl = true;
int spawnEnemies = 0;

std::array<int, 2> stairs_loc = { 0, 0 };

StartScreen* startScreen = new StartScreen();
DeathScreen* deathScreen = new DeathScreen();

PlayerCharacter* player;
EnemyCharacter* enemy[10] = { 0 };

GameMap* gameMap = new GameMap();
PlayerInfo* ui;

// Method Declarations
int randomNumber(int min, int max);

void clearMessage();
void fightMessage();

void updateSpecialMsg();

void drawGame();

bool placePlayer();
void updatePlayer();

bool placeStairs();
void updateStairs();

void spawnEnemy();
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

void fightMessage( int unitNum)
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
			
			messageStr += enemy[unitNum]->name + " for " + std::to_string(dmgDealtToEnemy) + " damage. ";
		}
		else messageStr += "missed! ";

		messageStr += enemy[unitNum]->name + " swung and ";
		if (wasPlayerHit)
		{
			if (enemyHitRoll[unitNum] == NAT_20) messageStr += "crit ";
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

void spawnEnemy()
{
	// randomly check for how many enemies to spawn based on floor
	// spawn said enemy
	// choose random room
	// place randomly in that room but not on top of any items
	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] != nullptr)
		{
			delete enemy[i];
			enemy[i] = nullptr;
		}
	}

	int minSpawns = 1 + (player->level / 5);
	int maxSpawns = 5 + (player->level / 5);

	spawnEnemies = randomNumber(minSpawns, maxSpawns);

	int roomToSpawn = 0;

	int x_start = 0;
	int y_start = 0;

	int x_size = 0;
	int y_size = 0;

	int x_pos = 0;
	int y_pos = 0;


	for (int i = 0; i < spawnEnemies; i++)
	{
		roomToSpawn = randomNumber(1, gameMap->numberOfRooms) - 1;
		x_start = gameMap->roomList[roomToSpawn]->x_start;
		y_start = gameMap->roomList[roomToSpawn]->y_start;

		x_size = gameMap->roomList[roomToSpawn]->x_size;
		y_size = gameMap->roomList[roomToSpawn]->y_size;

		x_pos = randomNumber(x_start + 1, x_start + x_size - 2);
		y_pos = randomNumber(y_start + 1, y_start + y_size - 2);

		enemy[i] = new Goblin();

		if (enemy[i]->setLocation(x_pos, y_pos))
		{
			gameMap->expMap[x_pos][y_pos] = 'G';
		}
	}
}

void updateEnemy()
{
	for (int i = 0; i < spawnEnemies; i++)
	{
		if (enemy[i] != nullptr)
		{
			if (enemy[i]->hitPoints > 0) gameMap->expMap[enemy[i]->x_pos][enemy[i]->y_pos] = enemy[i]->token;
			else
			{
				player->exp += enemy[i]->expReward;
				delete enemy[i];
				enemy[i] = nullptr;
			}
		}
	}
	
}

void moveEnemy()
{
	for (int i = 0; i < spawnEnemies; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->move(gameMap);
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

		player = new Fighter();
		ui = new PlayerInfo(player);

		player->name = startScreen->playerName;
		newLvl = true;

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
					destination.x = player->x_pos;
					destination.y = player->y_pos - 1;
					destination.token = gameMap->expMap[destination.x][destination.y];
					isFighting = !player->movePlayer(MOVE_UP, destination.token);
					break;
				case KEY_ARROW_DOWN:
					destination.x = player->x_pos;
					destination.y = player->y_pos + 1;
					destination.token = gameMap->expMap[destination.x][destination.y];
					isFighting = !player->movePlayer(MOVE_DOWN, destination.token);
					break;
				case KEY_ARROW_LEFT:
					destination.x = player->x_pos - 1;
					destination.y = player->y_pos;
					destination.token = gameMap->expMap[destination.x][destination.y];
					isFighting = !player->movePlayer(MOVE_LEFT, destination.token);
					break;
				case KEY_ARROW_RIGHT:
					destination.x = player->x_pos + 1;
					destination.y = player->y_pos;
					destination.token = gameMap->expMap[destination.x][destination.y];
					isFighting = !player->movePlayer(MOVE_RIGHT, destination.token);
					break;
				}

				updatePlayer();

				if (isFighting)
				{
					for (int i = 0; i < spawnEnemies; i++)
					{
						if ( enemy[i] != nullptr && destination.x == enemy[i]->x_pos && destination.y == enemy[i]->y_pos)
						{
							if (enemy[i]->hasShield)
							{
								playerHitRoll = player->attack();
								wasEnemyHit = (playerHitRoll >= (enemy[i]->armorClass + ShieldAC)); //player does damage
							}
							else
							{
								playerHitRoll = player->attack();
								wasEnemyHit = (playerHitRoll > enemy[i]->armorClass); //player does damage
							}

							if (wasEnemyHit) // player to enemy
							{
								if (playerHitRoll == NAT_20)
								{
									dmgDealtToEnemy = player->crit() + player->damage();
								}
								else dmgDealtToEnemy = player->damage();

								enemy[i]->hitPoints -= dmgDealtToEnemy;
							}
							else dmgDealtToEnemy = 0;

							if (player->hasShield)
							{
								enemyHitRoll[i] = enemy[i]->attack();
								wasPlayerHit = (enemyHitRoll[i] >= (player->armorClass + ShieldAC)); //enemy does damage
							}
							else
							{
								enemyHitRoll[i] = enemy[i]->attack();
								wasPlayerHit = (enemyHitRoll[i] > player->armorClass); //enemy does damage
							}

							if (wasPlayerHit) // enemy to player
							{
								if (enemyHitRoll[i] == NAT_20)
								{
									dmgDealtToPlayer = enemy[i]->crit() + enemy[0]->damage();
								}
								else dmgDealtToPlayer = enemy[i]->damage();

								player->hitPoints -= dmgDealtToPlayer;
							}
							else dmgDealtToPlayer = 0;

							fightMessage(i);
							break;
						}
					}
					
				}

			}
			if (input == KEY_e)
			{
				if (player->x_pos == stairs_loc[0] && player->y_pos == stairs_loc[1])
				{
					newLvl = true;
					player->floor++;
					player->exp += 100;
					continue;
				}
			}

			moveEnemy();
		}
	}

	return 0;
}