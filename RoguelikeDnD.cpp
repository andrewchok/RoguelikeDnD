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
#include "Message.h"

// Global Variables
// GAME_WIDTH + 1 (for \n)
int input = -1;
char specialMsg[GAME_WIDTH + 1] = { 0 };
std::string specialMsgStr = "";
std::string gameStr = "";

struct Destination
{
	char token;
	int x, y;
};

Destination destination;
bool isValidMove = false;
int playerHitRoll = 0;
int enemyHitRoll[10] = { 0 };
bool newLvl = true;
int spawnEnemies = 0;

StartScreen* startScreen = new StartScreen();
DeathScreen* deathScreen = new DeathScreen();

PlayerCharacter* player;
EnemyCharacter* enemy[10] = { 0 };

GameMap* gameMap = new GameMap();
PlayerInfo* ui;
Message* msg = new Message();;

// Method Declarations
int randomNumber(int min, int max);

void updateSpecialMsg();

void drawGame();

bool placePlayer();
void updatePlayer();

void spawnEnemy();
void updateEnemy();


// Method Definitions
int randomNumber(int min, int max)
{
	srand(unsigned(time(NULL) * 11 * rand()));
	int value = (rand() % (max - min + 1)) + min;
	return value;
}

void updateSpecialMsg()
{
	// write code to show special msg
	specialMsgStr = "";
	specialMsgStr = "Name:" + player->name + "     Level:" + std::to_string(player->level) + "    Class:" + player->dndClass + "\n" ;
}

void drawGame()
{
	gameStr = "";
	gameStr = msg->messageStr + gameMap->mapStr + ui->uiStr + specialMsgStr;
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
		else enemy[i] = nullptr;
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


		// Choose Enemy to spawn
		switch (randomNumber(1, 2))
		{
		case 1:
			enemy[i] = new Goblin();
			break;
		case 2:
			enemy[i] = new Vulture();
			break;
		default:
			enemy[i] = new Vulture();
		}

		if (enemy[i]->setLocation(x_pos, y_pos))
		{
			gameMap->expMap[x_pos][y_pos] = enemy[i]->token;
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

void battle()
{
	if (!isValidMove)
	{
		for (int i = 0; i < spawnEnemies; i++)
		{
			if (enemy[i] != nullptr && destination.x == enemy[i]->x_pos && destination.y == enemy[i]->y_pos)
			{
				int dmgDealtToEnemy = player->attack(enemy[i]);
				int dmgDealtToPlayer = enemy[i]->attack(player);

				msg->attackMessage(player, enemy[i], dmgDealtToEnemy, dmgDealtToPlayer);
				break;
			}
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

		while (true)
		{
			if (newLvl)
			{
				gameMap->createNewMap();
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
				updatePlayer();
			}
			updateEnemy();


			gameMap->makeExpMap();
			ui->updateUI();
			updateSpecialMsg();

			do
			{
				system("CLS");
				msg->popMessage();

				drawGame();
				if(!msg->messageQueue.empty())
				{
					while (!msg->messageQueue.empty())
					{
						input = _getch();
						if (input == KEY_SPACE) break;
					}
				}
				else input = _getch();
			}
			while (!msg->messageQueue.empty());


			if (player->hitPoints <= 0)
			{
				delete player;
				player = nullptr;
				deathScreen->drawDeathScreen();
				break;
			}

			if (input == KEY_BRANCH_0 || input == KEY_BRANCH_244)
			{
				input = _getch();

				//quit game funciton
				if (input == KEY_F12)
				{
					input = _getch();
					if (input == KEY_q) break;
					if (input == KEY_s) continue; //write save game function
					if (input == KEY_l) continue; //write load game function
				}
			}


			// Arrow key movement and wasd movement
			switch (input)
			{
			case KEY_ARROW_UP: case KEY_w:
				destination.x = player->x_pos;
				destination.y = player->y_pos - 1;
				destination.token = gameMap->expMap[destination.x][destination.y];
				isValidMove = player->movePlayer(MOVE_UP, destination.token);
				updatePlayer();
				battle();
				if (isValidMove) moveEnemy();
				break;
			case KEY_ARROW_DOWN: case KEY_s:
				destination.x = player->x_pos;
				destination.y = player->y_pos + 1;
				destination.token = gameMap->expMap[destination.x][destination.y];
				isValidMove = player->movePlayer(MOVE_DOWN, destination.token);
				updatePlayer();
				battle();
				if (isValidMove) moveEnemy();
				break;
			case KEY_ARROW_LEFT: case KEY_a:
				destination.x = player->x_pos - 1;
				destination.y = player->y_pos;
				destination.token = gameMap->expMap[destination.x][destination.y];
				isValidMove = player->movePlayer(MOVE_LEFT, destination.token);
				updatePlayer();
				battle();
				if (isValidMove) moveEnemy();
				break;
			case KEY_ARROW_RIGHT: case KEY_d:
				destination.x = player->x_pos + 1;
				destination.y = player->y_pos;
				destination.token = gameMap->expMap[destination.x][destination.y];
				isValidMove = player->movePlayer(MOVE_RIGHT, destination.token);
				updatePlayer();
				battle();
				if (isValidMove) moveEnemy();
				break;
			}			

			if (input == KEY_e)
			{
				if (player->x_pos == gameMap->stairs_loc[0] && player->y_pos == gameMap->stairs_loc[1])
				{
					newLvl = true;
					player->floor++;
					player->exp += 100;
					continue;
				}
			}
		}
	}

	return 0;
}