#pragma once
#ifndef MESSAGE
#define MESSAGE

#include <string>
#include <queue>
#include "Units.h"

class Message
{
public:

	std::queue<std::string> messageQueue;
	std::string messageStr = "";
	
	Message() {};
	~Message() {};

	void attackMessage(PlayerCharacter* player, EnemyCharacter* enemy, int dmgDealtToEnemy, int dmgDealtToPlayer)
	{
		messageStr = "";
		
		if (dmgDealtToEnemy > 0)
		{
			messageStr = "You swung and hit " + enemy->name + " for " + std::to_string(dmgDealtToEnemy) + " damage. ";
		}
		else
		{
			messageStr = "You swung and missed!";
		}

		messageQueue.push(messageStr);

		messageStr = "";

		if (enemy->hitPoints <= 0)
		{
			messageStr = enemy->name + " was defeated! You gained " + std::to_string(enemy->expReward) + " Exp!";
		}
		else 
		{
			if (dmgDealtToPlayer > 0)
			{
				messageStr = enemy->name + " swung and hit you for " + std::to_string(dmgDealtToPlayer) + " damage. ";
			}
			else
			{
				messageStr = enemy->name + " swung and missed!";
			}
		}

		messageQueue.push(messageStr);
	}

	void attackMessage(EnemyCharacter* enemy, int dmgDealtToPlayer)
	{
		messageStr = "";

		if (dmgDealtToPlayer > 0)
		{
			messageStr = enemy->name + " swung and hit you for " + std::to_string(dmgDealtToPlayer) + " damage. ";
		}
		else
		{
			messageStr = enemy->name + " swung and missed!";
		}

		messageQueue.push(messageStr);
	}

	void popMessage()
	{
		if (!messageQueue.empty())
		{
			messageStr = messageQueue.front();
			messageQueue.pop();

			if (!messageQueue.empty()) messageStr += " <more>\n";
			else messageStr += "\n";
		}
		else
		{
			messageStr = "\n";
		}
	}
};

#endif