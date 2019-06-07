#pragma once
#ifndef MESSAGE
#define MESSAGE

#include <string>
#include <queue>
#include "UnitsAndItems.h"
#include "Helper.h"

class Message
{
public:

	std::queue<std::string> messageQueue;
	std::string messageStr = "";
	
	Message() {};
	~Message() {};

	void floorMessage(int floor)
	{
		messageStr = "";

		messageStr = "Welcome to floor " + std::to_string(floor) + "!";

		messageQueue.push(messageStr);
	}

	void levelUpMessage(int level)
	{
		messageStr = "";

		messageStr = "Congratulations you are now level " + std::to_string(level) + "!";

		messageQueue.push(messageStr);
	}

	void playerAttackMessage(PlayerCharacter* player, EnemyCharacter* enemy, int dmgDealtToEnemy)
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
			messageQueue.push(messageStr);
		}
	}

	void enemyAttackMessage(EnemyCharacter* enemy, PlayerCharacter* player, int dmgDealtToPlayer)
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

	void goldMessage(int amount)
	{
		messageStr = "";
		
		messageStr = "You picked up " + std::to_string(amount) + " Gold! ";
		
		messageQueue.push(messageStr);
	}

	void rationMessage(PlayerCharacter* player)
	{
		messageStr = "";

		messageStr = "You picked up a Ration! You now have " + std::to_string(player->rations) + " Rations!";

		messageQueue.push(messageStr);
	}

	void eatCheckMessage(PlayerCharacter* player)
	{
		messageStr = "";

		messageStr = "You have " + std::to_string(player->rations) + " Rations, eat one? press <e> to eat";

		messageQueue.push(messageStr);
	}

	void hungryMessage()
	{
		messageStr = "";

		messageStr = "You are feeling hungry. You should eat something.";

		messageQueue.push(messageStr);

	}

	void hungryDmgMessage()
	{
		messageStr = "";

		messageStr = "The hunger is overwhelming. You took a damage.";

		messageQueue.push(messageStr);

	}

	void eatMessage()
	{
		messageStr = "";

		messageStr = "Yum! That was tasty.";

		messageQueue.push(messageStr);
	}

	void cantRestMessage(noRestReason reason)
	{
		messageStr = "";

		switch (reason)
		{
		case hunger:
			messageStr = "Cannot rest. Too hungry... Eat something!";
			break;
		case enemies:
			messageStr = "Cannot rest. Enemies still roaming the floor!";
			break;
		case restDice:
			messageStr = "Cannot short rest. A long rest is needed.";
			break;
		}
		

		messageQueue.push(messageStr);
	}

	void restPromptMessage()
	{
		messageStr = "";

		messageStr = "You have reached a Resting Area! press <1> short rest OR <2> long rest.";

		messageQueue.push(messageStr);
	}

	void shortRestMessage(int restDiceCount)
	{
		messageStr = "";

		messageStr = "You took a short rest. (" + std::to_string(restDiceCount) + " left)";

		messageQueue.push(messageStr);
	}

	void longRestMessage(int restDiceCount)
	{
		messageStr = "";

		messageStr = "You took a long rest. You now have " + std::to_string(restDiceCount) + " short rests.";

		messageQueue.push(messageStr);
	}

	void healMessage(int healAmt)
	{
		messageStr = "";

		messageStr = "You healed for " + std::to_string(healAmt) + ".";
		if (healAmt == 999) messageStr = "Fully Healed!";

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