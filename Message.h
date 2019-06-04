#pragma once
#ifndef MESSAGE
#define MESSAGE

#include <string>
#include <queue>

class Message
{
	std::queue<std::string> messageQueue = {};
	std::string messageStr = "";
	
	void clearMessage();
	void fightMessage(int unitNum);

	void clearMessage()
	{
		messageStr = "\n";
	}

	void fightMessage(int unitNum)
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
};

#endif