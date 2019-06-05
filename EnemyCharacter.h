#pragma once
#ifndef ENEMYCHARACTER
#define ENEMYCHARACTER
#include <string>
#include <time.h>
#include "Character.h"

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
	virtual void move(GameMap* map) = 0;


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
		std::array<direction, 4> moveDirection = { up, down, left, right };
		random_shuffle(moveDirection.begin(), moveDirection.end());

		for (auto dir : moveDirection)
		{
			switch (dir)
			{
			case up:
				if (isValidMove(map->map[this->x_pos][this->y_pos - 1]))
				{
					if (isBlocked(map->expMap[this->x_pos][this->y_pos - 1])) return;
					this->y_pos--;
					return;
				}
				break;
			case down:
				if (isValidMove(map->map[this->x_pos][this->y_pos + 1]))
				{
					if (isBlocked(map->expMap[this->x_pos][this->y_pos + 1])) return;
					this->y_pos++;
					return;
				}
				break;
			case left:
				if (isValidMove(map->map[this->x_pos - 1][this->y_pos]))
				{
					if (isBlocked(map->expMap[this->x_pos - 1][this->y_pos])) return;
					this->x_pos--;
					return;
				}
				break;
			case right:
				if (isValidMove(map->map[this->x_pos + 1][this->y_pos]))
				{
					if (isBlocked(map->expMap[this->x_pos + 1][this->y_pos])) return;
					this->x_pos++;
					return;
				}
				break;
			}
		}
	}

	void idle() {};
	
	bool canSeePlayer()
	{
		return true;
	};
};

#endif