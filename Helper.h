#pragma once
#ifndef HELPER
#define HELPER

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <conio.h>
#include <time.h>
#include <array>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
#include <queue>

// ============================
// ========= DEFINES ==========
// ============================

#define NAT_20 99
#define NAT_1 -99
#define SHIELD_AC 2 
#define FULL_HEAL 999
#define SHORT_REST_HUNGER_COST 25
#define LONG_REST_HUNGER_COST 325

// ============================
// ========== ENUMS ===========
// ============================

enum Direction
{
	up,
	right,
	down,
	left
};

enum DmgType
{
	Acid,
	Bludgeoning,
	Cold,
	Fire,
	Force,
	Lightning,
	Necrotic,
	Piercing,
	Poison,
	Psychic,
	Radiant,
	Slashing,
	Thunder
};

enum noRestReason
{
	hunger,
	enemies,
	restDice
};

enum RoomNumber
{
	ROOM_INVALID,
	ROOM_ONE,	// Top-Left
	ROOM_TWO,	// Top-Center
	ROOM_THREE,	// Top-Right
	ROOM_FOUR,	// Center-Left
	ROOM_FIVE,	// Center
	ROOM_SIX,	// Center-Right
	ROOM_SEVEN,	// Bottom-Left
	ROOM_EIGHT,	// Bottom-Center
	ROOM_NINE	// Bottom-Right
};

enum DoorOrientation
{
	DOOR_TOP,
	DOOR_RIGHT,
	DOOR_BOTTOM,
	DOOR_LEFT
};

// ============================
// ========= STRUCTS ==========
// ============================

struct Coordinate
{
	int x = -1 , y = -1;
};

struct Destination
{
	char token;
	int x, y;
};

struct door
{
	DoorOrientation ori;
	int x_loc, y_loc;
};

// ============================
// ========= METHODS ==========
// ============================

int randomNumber(int min, int max)
{
	srand(unsigned(time(NULL) * 11 * rand()));
	int value = (rand() % (max - min + 1)) + min;
	return value;
}

#endif