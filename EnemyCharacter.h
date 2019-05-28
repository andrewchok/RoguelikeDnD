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

	// ============================
	// ========= METHODS ==========
	// ============================

	EnemyCharacter() {};
	virtual ~EnemyCharacter() {};

	virtual int attack() = 0;
	virtual int damage() = 0;

	virtual void move() = 0;
	virtual void idle() = 0;
	virtual bool canSeePlayer() = 0;
};

#endif