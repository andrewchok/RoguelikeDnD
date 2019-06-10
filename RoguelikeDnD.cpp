#include "Helper.h"
#include "KeyStrokes.h"
#include "UnitsAndItems.h"
#include "GameMap.h"
#include "PlayerInfo.h"
#include "StartScreen.h"
#include "InfoScreen.h"
#include "DeathScreen.h"
#include "Message.h"

// Variables

// This will capture the players key strokes as inputs
int input = -1;

// This is a special area where the player name among other things will be displayed
std::string specialMsgStr = "";

// This will hold all the text to presented in game when its needs to be updated
std::string gameStr = "";

// Holds the destination x & y location in the grid and its token value
Destination destination;

// flag to check if player move is valid
bool isValidMove = false;

// flag to see if it is a new floor
bool newFloor = true;

// number of enemies to spawn in the game
int spawnEnemies = 0;

// number of items to spawn in the game
int spawnItems = 0;

// flag to check if eating
bool isEating = false;

// flag to check if can rest
bool canRest = false;

// holds the amount player will heal for
int healAmt = 0;

// various screen used in the game
StartScreen* startScreen = new StartScreen();
InfoScreen* infoScreen = new InfoScreen();
DeathScreen* deathScreen = new DeathScreen();

// This is the player class
PlayerCharacter* player;

// This is an array of items that can spawn in the game where the cap is 10
Item* item[10] = { 0 };

// This is an array of enemies that can spawn in the game where the cap is 10
EnemyCharacter* enemy[10] = { 0 };

// This will hold messages to display to the player for various events
Message* msg = new Message();

// This holds the game map that is created and displayed
GameMap* gameMap = new GameMap();

// This will hold the players character information in the game
PlayerInfo* ui;


// Method Declarations

void updateSpecialMsg();

void spawnItem();
void updateItem();

void eatCheck();

void restCheck();

bool placePlayer();
void updatePlayer();

void spawnEnemy();
void updateEnemy();

void drawGame();


// Method Definitions

void updateSpecialMsg()
{
	// write code to show special msg
	specialMsgStr = "";
	specialMsgStr = "Name:" + player->name + "     Level:" + std::to_string(player->level) + "    Class:" + player->dndClass + "    Rations:" + std::to_string(player->rations) + "(5)\n" ;
}

// randomly check for how many items to spawn 1-10
// choose random room to spawn
// place randomly in that room but not on top of stairs
void spawnItem()
{
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
		switch (randomNumber(1, 7))
		{
		case 1:
			item[i] = new Ration();
			break;
		case 2: case 3: case 4: case 5: case 6: case 7:
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

// updates the state of all the items in the game
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

// checks if the player wants to eat
void eatCheck()
{
	msg->eatCheckMessage(player);
	msg->popMessage();

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

			drawGame();
		}
	}
	else
	{
		msg->popMessage();
		drawGame();
	}

	isEating = false;
}

// checks if the player can rest (if all enemies are defeated on current floor)
// and checks if the player wants to short or long rest
void restCheck()
{
	msg->restPromptMessage();
	msg->popMessage();

	drawGame();
	input = _getch();
	if ( input == KEY_1 )
	{
		// short rest
		if (player->hunger > SHORT_REST_HUNGER_COST && player->restDiceCurrentCount > 0)
		{
			player->hunger -= SHORT_REST_HUNGER_COST;
			player->restDiceCurrentCount--;

			msg->shortRestMessage(player->restDiceCurrentCount);

			healAmt = randomNumber(1, player->restDiceType) + player->modCON;
			player->hitPoints += healAmt;
			if (player->hitPoints > player->maxHitPoints)
			{
				player->hitPoints = player->maxHitPoints;
				healAmt = FULL_HEAL;
			}

			msg->healMessage(healAmt);
		}
		else
		{
			if (player->hunger <= SHORT_REST_HUNGER_COST)
			{
				msg->cantRestMessage(hunger);
			}
			else if (player->restDiceCurrentCount <= 0)
			{
				msg->cantRestMessage(restDice);
			}
		}
	}
	else if( input == KEY_2 )
	{
		// long rest
		if (player->hunger > LONG_REST_HUNGER_COST)
		{
			player->hunger -= LONG_REST_HUNGER_COST;

			player->restDiceCurrentCount = player->restDiceMaxCount;
			msg->longRestMessage(player->restDiceCurrentCount);

			player->hitPoints = player->maxHitPoints;
			healAmt = FULL_HEAL;
			msg->healMessage(healAmt);
		}
		else
		{
			msg->cantRestMessage(hunger);
		}
	}

	canRest = false;
}

// places the player on the floor by:
// choose random room
// place randomly in that room 
bool placePlayer()
{
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

// updates the state of player in the game
void updatePlayer()
{
	gameMap->expMap[player->location.x][player->location.y] = '@';
	if (player->levelUp()) msg->levelUpMessage(player->level);
}


// randomly check for how many enemies to spawn based on player level
// types of enemies depend on current floor
// choose random room to spawn enemies
void spawnEnemy()
{
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
		int minChallenge = player->floor / 10;
		if (minChallenge > 6) minChallenge = 6;
		int maxChallenge = (player->floor + 10) / 5;
		if (maxChallenge > 6) maxChallenge = 6;

		int challenge = randomNumber(minChallenge, maxChallenge);

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

// updates the state of all the enemies in the game
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

// passes the enemy (if it is not null) to a movement algorithm 
// and checks if the enemy is fighting the player
void moveEnemy()
{
	for (int i = 0; i < spawnEnemies; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->move(gameMap, player);
			if (enemy[i]->isFighting)
			{
				int dmgDealtToPlayer = enemy[i]->attack(player);
				msg->enemyAttackMessage(enemy[i], player, dmgDealtToPlayer);
			}
		}
	}
}

// method to check if the player is moving into an enemy to trigger player attack
void battle()
{
	if (player->isFighting)
	{
		for (int i = 0; i < spawnEnemies; i++)
		{
			if (enemy[i] != nullptr && destination.x == enemy[i]->location.x && destination.y == enemy[i]->location.y)
			{
				int dmgDealtToEnemy = player->attack(enemy[i]);
				msg->playerAttackMessage(player, enemy[i], dmgDealtToEnemy);
				break;
			}
		}
	}
}

// puts all the information together into gameStr to print
void drawGame()
{
	system("CLS");
	gameStr = "";
	gameStr = msg->messageStr + gameMap->mapStr + ui->uiStr + specialMsgStr;
	std::cout << gameStr;
}

// Main function
int main()
{
	// Entire Program loop
	while (true)
	{
		// show start screen
		startScreen->drawStartScreen();
		if (startScreen->playerName == "quit") break;

		// show info screen
		infoScreen->drawInfoScreen();

		// create new player character instance for new game
		player = new Fighter();
		ui = new PlayerInfo(player);

		player->name = startScreen->playerName;
		newFloor = true;
		
		// Game loop
		while (true)
		{
			// checks if new level
			if (newFloor)
			{
				gameMap->createNewMap();
				placePlayer();
				gameMap->explore(player->location.x, player->location.y);
				gameMap->refreshExpMap();

				updatePlayer();
				spawnEnemy();
				spawnItem();

				msg->floorMessage(player->floor);
				newFloor = false;
			}
			else
			{
				gameMap->explore(player->location.x, player->location.y);
				gameMap->refreshExpMap();
				updatePlayer();
			}
			updateItem();
			updateEnemy();
			
			// if hunger, alert player
			if (player->hunger <= 0) msg->hungryDmgMessage();
			else if (player->hunger <= HUNGER) msg->hungryMessage();

			gameMap->makeExpMap();
			ui->updateUI();
			updateSpecialMsg();
			
			// if multiple messages, stop player to read
			do
			{
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

			// if player is dead, show death screen
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
					if (input == KEY_s) continue; //write save game function (future)
					if (input == KEY_l) continue; //write load game function (future)
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
				updateEnemy();
				if (isValidMove || player->isFighting) moveEnemy();
				break;
			case KEY_ARROW_DOWN: case KEY_s:
				destination.x = player->location.x;
				destination.y = player->location.y + 1;
				destination.token = gameMap->expMap[destination.x][destination.y];
				isValidMove = player->movePlayer(down, destination.token);
				updatePlayer();
				battle();
				updateEnemy();
				if (isValidMove || player->isFighting) moveEnemy();
				break;
			case KEY_ARROW_LEFT: case KEY_a:
				destination.x = player->location.x - 1;
				destination.y = player->location.y;
				destination.token = gameMap->expMap[destination.x][destination.y];
				isValidMove = player->movePlayer(left, destination.token);
				updatePlayer();
				battle();
				updateEnemy();
				if (isValidMove || player->isFighting) moveEnemy();
				break;
			case KEY_ARROW_RIGHT: case KEY_d:
				destination.x = player->location.x + 1;
				destination.y = player->location.y;
				destination.token = gameMap->expMap[destination.x][destination.y];
				isValidMove = player->movePlayer(right, destination.token);
				updatePlayer();
				battle();
				updateEnemy();
				if (isValidMove || player->isFighting) moveEnemy();
				break;
			}			

			// trigger using stairs or rest area event
			if (input == KEY_e)
			{
				if (player->location.x == gameMap->stairs_loc.x && player->location.y == gameMap->stairs_loc.y)
				{
					newFloor = true;
					player->floor++;
					player->exp += 100;
					continue;
				}

				if (player->location.x == gameMap->restArea_loc.x && player->location.y == gameMap->restArea_loc.y)
				{
					canRest = true;
					for (auto en : enemy)
					{
						if (en != nullptr)
						{
							canRest = false;
							break;
						}
					}

					if (canRest)
					{
						restCheck();
					}
					else msg->cantRestMessage(enemies);
					continue;
				}
			}

			// trigger eating event
			if (input == KEY_f)
			{
				isEating = true;
				continue;
			}
		}
	}

	return 0;
}