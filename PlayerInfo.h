#pragma once
#ifndef PLAYERINFO
#define PLAYERINFO

#include <string>
#include "Units.h"

class PlayerInfo
{
public:

	std::string uiStr = "";
	PlayerCharacter* player;

	PlayerInfo(PlayerCharacter* player)
	{
		/* Floor [0 - 9] values [6 - 8]
		 * ui[0 - 9] = "Floor:999 "
		 *
		 * Hit Points (HP) [10 - 21] values [13 - 20]
		 * ui[10 - 21] = "HP:999(999) "
		 *
		 * Armor Class (AC) [22 - 27] values [25 - 26]
		 * ui[22 - 27] = "AC:99 "
		 *
		 * Attack Bonus (Atk) [28 - 35] values [32 - 34]
		 * ui[28 - 35] = "Atk:+99 "
		 *
		 * Damage Roll (Dmg) [36 - 45] values [40 - 44]
		 * ui[36 - 45] = "Dmg:99d20 "
		 *
		 * Gold [46 - 56] values [51 - 55]
		 * for this Roguelike Gold will be equivalent to Silver Pieces
		 * ui[46 - 56] = "Gold:99999 "
		 *
		 * Experience Points (Exp) [57 - 67] values [61 - 66]
		 * ui[57 - 67] = "Exp:999999 "
		 *
		 * Hunger [68 - 78] values [75 - 77]
		 * for this Rogue like having Hunger management increases the difficulty
		 * ui[68 - 78] = "Hunger:999\n"
		 */

		uiStr = "Floor:999 HP:999(999) AC:99 Atk:+99 Dmg:99d99 Gold:99999 Exp:999999 Hunger:999\n";
		this->player = player;
	}

	void updateUI()
	{
		std::string str = "";
		// Floor [6 - 8]
		str = std::to_string(player->floor);
		str.resize(4);
		uiStr.replace(6, 4, str);
		// Hit Points (HP) values [13 - 20]
		str = std::to_string(player->hitPoints) + "(" + std::to_string(player->maxHitPoints) + ")";
		str.resize(8);
		uiStr.replace(13, 8, str);
		// Armor Class (AC) values [25 - 26]
		if (player->hasShield) str = std::to_string(player->armorClass + 2);
		else str = std::to_string(player->armorClass);
		str.resize(3);
		uiStr.replace(25, 3, str);
		// Attack Bonus (Atk) values [32 - 34]
		str = "+" + std::to_string(player->proficiencyBonus + player->modSTR);
		str.resize(4);
		uiStr.replace(32, 4, str);
		// Damage Roll (Dmg) values [40 - 44]
		str = player->dmgRoll;
		str.resize(6);
		uiStr.replace(40, 6, str);
		// Gold values [51 - 55]
		str = std::to_string(player->gold);
		str.resize(6);
		uiStr.replace(51, 6, str);
		// Experience Points (Exp) values [61 - 66]
		str = std::to_string(player->exp);
		str.resize(7);
		uiStr.replace(61, 7, str);
		// Hunger values [75 - 77]
		str = std::to_string(player->hunger / 10);
		str.resize(3);
		uiStr.replace(75, 3, str);
	}
};

#endif

