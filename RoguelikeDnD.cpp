#include "Helper.h"
#include "KeyStrokes.h"
#include "UnitsAndItems.h"
#include "GameMap.h"
#include "PlayerInfo.h"
#include "StartScreen.h"
#include "DeathScreen.h"
#include "Message.h"

// Global Variables
// GAME_WIDTH + 1 (for \n)
int input = -1;
std::string specialMsgStr = "";
std::string gameStr = "";

Destination destination;
bool isValidMove = false;
int enemyHitRoll[10] = { 0 };
bool newLvl = true;
int spawnEnemies = 0;
int spawnItems = 0;
bool isEating = false;

StartScreen* startScreen = new StartScreen();
DeathScreen* deathScreen = new DeathScreen();

PlayerCharacter* player;
Item* item[10] = { 0 };
EnemyCharacter* enemy[10] = { 0 };

Message* msg = new Message();
GameMap* gameMap = new GameMap();
PlayerInfo* ui;


// Method Declarations
int randomNumber(int min, int max);

void updateSpecialMsg();

void drawGame();

void spawnItem();
void updateItem();

void eatCheck();

bool placePlayer();
void updatePlayer();

void spawnEnemy();
void updateEnemy();


// Method Definitions

void updateSpecialMsg()
{
	// write code to show special msg
	specialMsgStr = "";
	specialMsgStr = "Name:" + player->name + "     Level:" + std::to_string(player->level) + "    Class:" + player->dndClass + "    Rations:" + std::to_string(player->rations) + "(5)\n" ;
}

void drawGame()
{
	gameStr = "";
	gameStr = msg->messageStr + gameMap->mapStr + ui->uiStr + specialMsgStr;
	std::cout << gameStr;
}

void spawnItem()
{

	// randomly check for how many items to spawn 1-10
	// choose random room to spawn
	// place randomly in that room but not on top of stairs
	for (int i = 0; i < 10; i++)
	{
		if (item[i] != nullptr)
		{
			delete item[i];
			item[i] = nullptr;
		}
		else item[i] = nullptr;
	}

	int minSpawns = 1;
	int maxSpawns = 10;

	spawnItems = randomNumber(minSpawns, maxSpawns);

	int roomToSpawn = 0;

	int x_start = 0;
	int y_start = 0;

	int x_size = 0;
	int y_size = 0;

	int x_pos = 0;
	int y_pos = 0;


	for (int i = 0; i < spawnItems; i++)
	{
		// Choose item to spawn
		switch (randomNumber(1, 5))
		{
		case 1:
			item[i] = new Ration();
			break;
		case 2: case 3: case 4: case 5:
			item[i] = new Gold();
			break;
		default:
			item[i] = new Gold();
		}

		do
		{
			roomToSpawn = randomNumber(1, gameMap->numberOfRooms) - 1;
			x_start = gameMap->roomList[roomToSpawn]->x_start;
			y_start = gameMap->roomList[roomToSpawn]->y_start;

			x_size = gameMap->roomList[roomToSpawn]->x_size;
			y_size = gameMap->roomList[roomToSpawn]->y_size;

			x_pos = randomNumber(x_start + 1, x_start + x_size - 2);
			y_pos = randomNumber(y_start + 1, y_start + y_size - 2);

		}
		while (!(item[i]->setLocation(x_pos, y_pos, gameMap->stairs_loc, player->location)));
	}
}

void updateItem()
{
	for (int i = 0; i < spawnItems; i++)
	{
		if (item[i] != nullptr)
		{
			if (item[i]->location.x == player->location.x && item[i]->location.y == player->location.y) 
			{
				if (item[i]->name == "Gold")
				{
					player->gold += item[i]->amount;
					msg->goldMessage(item[i]->amount);
					delete item[i];
					item[i] = nullptr;
				}
				else if (item[i]->name == "Ration" && player->rations < 5)
				{
					player->rations += 1;
					msg->rationMessage(player);
					delete item[i];
					item[i] = nullptr;
				}
			}
			else
			{
				if (gameMap->isExplored[item[i]->location.x][item[i]->location.y])
				{
					gameMap->expMap[item[i]->location.x][item[i]->location.y] = item[i]->token;
				}
			}
		}
	}
}

void eatCheck()
{
	msg->eatCheckMessage(player);
	msg->popMessage();

	system("CLS");
	drawGame();
	input = _getch();
	if (input == KEY_e)
	{
		if (player->rations > 0)
		{
			player->rations--;
			player->hunger += 350;
			if (player->hunger > 500) player->hunger = 500;
			msg->eatMessage();
			msg->popMessage();

			ui->updateUI();
			updateSpecialMsg();

			system("CLS");
			drawGame();
		}
	}
	else
	{
		msg->popMessage();
		system("CLS");
		drawGame();
	}

	isEating = false;
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
	gameMap->expMap[player->location.x][player->location.y] = '@';
	if (player->levelUp()) msg->levelUpMessage(player->level);
}

void spawnEnemy()
{
	// randomly check for how many enemies to spawn based on player level
	// types of enemies depend on current floor
	// choose random room to spawn enemies
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

		int challenge = randomNumber(0, 6);


		// Choose Enemy to spawn
		switch (challenge)
		{
		case 0: // Challenge Rating 0
			switch (randomNumber(0, 1)) 
			{
			case 0:
				enemy[i] = new Jackal();
				break;
			case 1:
				enemy[i] = new Vulture();
				break;
			}
			break;
		case 1: // Challenge Rating 1/8
			switch (randomNumber(0, 1))
			{
			case 0:
				enemy[i] = new Kobold();
				break;
			case 1:
				enemy[i] = new Cultist();
				break;
			}
			break;
		case 2: // Challenge Rating 1/4
			switch (randomNumber(0, 2))
			{
			case 0:
				enemy[i] = new Goblin();
				break;
			case 1:
				enemy[i] = new Skeleton();
				break;
			case 2:
				enemy[i] = new Zombie();
				break;
			}
			break;
		case 3: // Challenge Rating 1/2
			switch (randomNumber(0, 2))
			{
			case 0:
				enemy[i] = new Hobgoblin();
				break;
			case 1:
				enemy[i] = new Orc();
				break;
			case 2:
				enemy[i] = new Thug();
				break;
			}
			break;
		case 4: // Challenge Rating 1
			enemy[i] = new Bugbear();
			break;
		case 5: // Challenge Rating 2
			enemy[i] = new Merrow();
			break;
		case 6: // Challenge Rating 3
			switch (randomNumber(0, 1))
			{
			case 0:
				enemy[i] = new Nightmare();
				break;
			case 1:
				enemy[i] = new WinterWolf();
				break;
			}
			break;
		default:
			enemy[i] = new Vulture();
		}

		do
		{
			roomToSpawn = randomNumber(1, gameMap->numberOfRooms) - 1;
			x_start = gameMap->roomList[roomToSpawn]->x_start;
			y_start = gameMap->roomList[roomToSpawn]->y_start;

			x_size = gameMap->roomList[roomToSpawn]->x_size;
			y_size = gameMap->roomList[roomToSpawn]->y_size;

			x_pos = randomNumber(x_start + 1, x_start + x_size - 2);
			y_pos = randomNumber(y_start + 1, y_start + y_size - 2);

		}
		while (!(enemy[i]->setLocation(x_pos, y_pos, player->location)));
	}
}

void updateEnemy()
{
	for (int i = 0; i < spawnEnemies; i++)
	{
		if (enemy[i] != nullptr)
		{
			if (enemy[i]->hitPoints > 0)
			{
				if (enemy[i]->canSeePlayer(player, gameMap)) gameMap->expMap[enemy[i]->location.x][enemy[i]->location.y] = enemy[i]->token;
			}
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
	if (player->isFighting)
	{
		for (int i = 0; i < spawnEnemies; i++)
		{
			if (enemy[i] != nullptr && destination.x == enemy[i]->location.x && destination.y == enemy[i]->location.y)
			{
				int dmgDealtToEnemy = player->attack(enemy[i]);
				int dmgDealtToPlayer = enemy[i]->attack(player);

				msg->attackMessage(player, enemy[i], dmgDealtToEnemy, dmgDealtToPlayer);
				break;
			}
		}
		player->isFighting = false;
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
				gameMap->explore(player->location.x, player->location.y);
				gameMap->refreshExpMap();

				updatePlayer();
				spawnEnemy();
				spawnItem();

				msg->floorMessage(player->floor);
				newLvl = false;
			}
			else
			{
				gameMap->explore(player->location.x, player->location.y);
				gameMap->refreshExpMap();
				updatePlayer();
			}
			updateItem();
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
			}
			while (!msg->messageQueue.empty());

			if (isEating) eatCheck();
			
			input = _getch();

			if (player->hitPoints <= 0)
			{
				deathScreen->drawDeathScreen();
				deathScreen->showStats(player);
				delete player;
				player = nullptr;
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
				destination.x = player->location.x;
				destination.y = player->location.y - 1;
				destination.token = gameMap->expMap[destination.x][destination.y];
				isValidMove = player->movePlayer(up, destination.token);
				updatePlayer();
				battle();
				if (isValidMove) moveEnemy();
				break;
			case KEY_ARROW_DOWN: case KEY_s:
				destination.x = player->location.x;
				destination.y = player->location.y + 1;
				destination.token = gameMap->expMap[destination.x][destination.y];
				isValidMove = player->movePlayer(down, destination.token);
				updatePlayer();
				battle();
				if (isValidMove) moveEnemy();
				break;
			case KEY_ARROW_LEFT: case KEY_a:
				destination.x = player->location.x - 1;
				destination.y = player->location.y;
				destination.token = gameMap->expMap[destination.x][destination.y];
				isValidMove = player->movePlayer(left, destination.token);
				updatePlayer();
				battle();
				if (isValidMove) moveEnemy();
				break;
			case KEY_ARROW_RIGHT: case KEY_d:
				destination.x = player->location.x + 1;
				destination.y = player->location.y;
				destination.token = gameMap->expMap[destination.x][destination.y];
				isValidMove = player->movePlayer(right, destination.token);
				updatePlayer();
				battle();
				if (isValidMove) moveEnemy();
				break;
			}			

			if (input == KEY_e)
			{
				if (player->location.x == gameMap->stairs_loc.x && player->location.y == gameMap->stairs_loc.y)
				{
					newLvl = true;
					player->floor++;
					player->exp += 100;
					continue;
				}
			}

			if (input == KEY_f)
			{
				isEating = true;
			}
		}
	}

	return 0;
}