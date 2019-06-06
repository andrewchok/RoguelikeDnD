#pragma once
#ifndef ENEMYCHARACTER
#define ENEMYCHARACTER
#include <string>
#include <time.h>
#include "Character.h"
#include "GameMap.h"

class EnemyCharacter : public Character
{
public:

	// ============================
	// ======== VARIABLES =========
	// ============================

	// Enemy Info
	int expReward = 0;
	int hitModifier = 0;

	// ============================
	// ========= METHODS ==========
	// ============================

	EnemyCharacter() {};
	virtual ~EnemyCharacter() {};

	virtual int crit() = 0;
	virtual int damage() = 0;

	bool canSeePlayer(Character* player, GameMap* gameMap)
	{
		if (checkSurrounding(player)) return true;

		bool visited[GAME_WIDTH][GAME_MAP_HEIGHT] = { false };

		return checkRoom(this->location.x, this->location.y, player->location.x, player->location.y, gameMap, visited);
	};

	void idle() {};

	void move(GameMap* map)
	{
		if (roll(1, 3) == 1)
		{
			idle();
		}
		else
		{
			randomMove(map);
		}
	};

	int attack(Character* player)
	{
		if (this->hitPoints <= 0) return 0;

		int dmgDealtToPlayer = 0;

		int roll = roll20();
		roll = (roll == NAT_20) ? NAT_20 : roll + hitModifier;

		// player does damage if roll >= to enemy AC
		if (roll >= (player->hasShield ? player->armorClass + ShieldAC : player->armorClass))
		{
			dmgDealtToPlayer = (roll == NAT_20) ? this->damage() + this->crit() : this->damage();
			player->hitPoints -= dmgDealtToPlayer;
		}

		return dmgDealtToPlayer;
	};

	bool isBlocked(char destination)
	{
		if (isFighting(destination)) 
		{
			//fight!!! 
			return true;
		}
		if (destination == 'J') return true;
		if (destination == 'V') return true;
		if (destination == 'K') return true;
		if (destination == 'C') return true;
		if (destination == 'G') return true;
		if (destination == 'S') return true;
		if (destination == 'Z') return true;
		if (destination == 'H') return true;
		if (destination == 'O') return true;
		if (destination == 'T') return true;
		if (destination == 'B') return true;
		if (destination == 'M') return true;
		if (destination == 'N') return true;
		if (destination == 'W') return true;

		return false;
	}

	bool isFighting(char destination)
	{
		if (destination == '@') return true;
		return false;
	}

	bool isValidMove(char destination)
	{
		if (destination == ' ' || destination == '-' || destination == '|')
		{
			return false;
		}

		return true;
	}

	void randomMove(GameMap* map)
	{
		std::array<Direction, 4> moveDirection = { up, down, left, right };
		random_shuffle(moveDirection.begin(), moveDirection.end());

		for (auto dir : moveDirection)
		{
			switch (dir)
			{
			case up:
				if (isValidMove(map->map[this->location.x][this->location.y - 1]))
				{
					if (isBlocked(map->expMap[this->location.x][this->location.y - 1])) return;
					this->location.y--;
					return;
				}
				break;
			case down:
				if (isValidMove(map->map[this->location.x][this->location.y + 1]))
				{
					if (isBlocked(map->expMap[this->location.x][this->location.y + 1])) return;
					this->location.y++;
					return;
				}
				break;
			case left:
				if (isValidMove(map->map[this->location.x - 1][this->location.y]))
				{
					if (isBlocked(map->expMap[this->location.x - 1][this->location.y])) return;
					this->location.x--;
					return;
				}
				break;
			case right:
				if (isValidMove(map->map[this->location.x + 1][this->location.y]))
				{
					if (isBlocked(map->expMap[this->location.x + 1][this->location.y])) return;
					this->location.x++;
					return;
				}
				break;
			}
		}
	}
		
	bool checkRoom(int start_x, int start_y, int end_x, int end_y, GameMap* gameMap, bool visited[GAME_WIDTH][GAME_MAP_HEIGHT])
	{
		if (start_x >= GAME_WIDTH || start_y >= GAME_MAP_HEIGHT) return false;
		if (start_x < 0 || start_y < 0) return false;
		if (visited[start_x][start_y] == true) return false;
		if (!(gameMap->map[start_x][start_y] == '.' || gameMap->map[start_x][start_y] == '%')) return false;
		if (start_x == end_x && start_y == end_y) return true;

		visited[start_x][start_y] = true;

		if (checkRoom(start_x - 1, start_y - 1, end_x, end_y, gameMap, visited)) return true;
		if (checkRoom(start_x - 1, start_y, end_x, end_y, gameMap, visited)) return true;
		if (checkRoom(start_x - 1, start_y + 1, end_x, end_y, gameMap, visited)) return true;
		if (checkRoom(start_x, start_y - 1, end_x, end_y, gameMap, visited)) return true;
		if (checkRoom(start_x, start_y + 1, end_x, end_y, gameMap, visited)) return true;
		if (checkRoom(start_x + 1, start_y - 1, end_x, end_y, gameMap, visited)) return true;
		if (checkRoom(start_x + 1, start_y, end_x, end_y, gameMap, visited)) return true;
		if (checkRoom(start_x + 1, start_y + 1, end_x, end_y, gameMap, visited)) return true;
	}

	bool checkSurrounding(Character* player)
	{
		if ((this->location.x == player->location.x || this->location.x + 1 == player->location.x || this->location.x - 1 == player->location.x) &&
			(this->location.y == player->location.y || this->location.y + 1 == player->location.y || this->location.y - 1 == player->location.y)) return true;
		else return false;
	}

	bool setLocation(int x_pos, int y_pos, Coordinate player_loc)
	{
		if (x_pos > 0 && x_pos < 80 && y_pos > 0 && y_pos < 23)
		{
			if (x_pos == player_loc.x && y_pos < player_loc.y) return false;

			this->location.x = x_pos;
			this->location.y = y_pos;
			return true;
		}
		return false;
	};
};

#endif