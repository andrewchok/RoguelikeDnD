#pragma once
#ifndef GAMEMAP
#define GAMEMAP

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <conio.h>
#include <time.h>
#include <array>
#include <algorithm>
#include "Room.h"
#include <vector>
#include <random>
#include <chrono>
#include "Units.h"

// Game dimension constants
const int GAME_WIDTH = 80;
const int GAME_HEIGHT = 25;
const int GAME_MAP_HEIGHT = 23;

class GameMap
{
public:
	// Global Variables
	// GAME_WIDTH + 1 (for \n)
	int input = -1;
	char map[GAME_WIDTH + 1][GAME_MAP_HEIGHT] = { 0 };
	char expMap[GAME_WIDTH + 1][GAME_MAP_HEIGHT] = { 0 };	// exp -> explored
	std::string mapStr = "";
	std::string gameStr = "";
	char destination = ' ';
	bool newLvl = true;

	// new variables
	int enemyCount = 5;
	//char enemy[10] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };

	std::array<int, 9> roomNumberList{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int numberOfRooms = 0;
	std::vector<Room*> roomList = {};

	enum direction
	{
		up,
		right,
		down,
		left
	};

	struct Coordinate
	{
		int x, y;
	};

	std::vector<Coordinate> doorLocations;

	GameMap() { clearExpMap(); };
	~GameMap() {};

	int randomNumber(int min, int max)
	{
		srand(unsigned(time(NULL) * 11 * rand()));
		int value = (rand() % (max - min + 1)) + min;
		return value;
	}

	bool drawRoom(Room * room)
	{
		for (int y = room->y_start; y < room->y_start + room->y_size; y++)
		{
			for (int x = room->x_start; x < (room->x_start + room->x_size) && y == room->y_start; x++)
			{
				expMap[x][y] = '-';
			}

			for (int x = room->x_start; x < (room->x_start + room->x_size) && y > room->y_start && y < (room->y_start + room->y_size - 1); x++)
			{
				if (x == room->x_start || x == (room->x_start + room->x_size - 1))
				{
					expMap[x][y] = '|';
				}
				else
				{
					expMap[x][y] = '.';
				}

			}

			for (int x = room->x_start; x < (room->x_start + room->x_size) && y == (room->y_start + room->y_size - 1); x++)
			{
				expMap[x][y] = '-';
			}
		}
		return true;
	}


	bool createRoom(RoomNumber room)
	{
		// size of room
		int x_size = randomNumber(4, 24);
		int y_size = randomNumber(4, 7);

		// location of top left corner of room
		int x_start = randomNumber(0, 25 - x_size + 1);
		int y_start = randomNumber(0, 6 - y_size + 1);


		Room* tempRoom = new Room(room, x_start, y_start, x_size, y_size);
		roomList.push_back(tempRoom);

		drawRoom(tempRoom);

		return true;
	}

	void drunkWalkCorridor(int x, int y, DoorOrientation door)
	{
		enum direction
		{
			up,
			right,
			down,
			left
		};

		direction lastWalk = (direction)door;
		direction nextWalk = (direction)door;
		char destination = ' ';
		int walk = 0;

		while (destination == ' ')
		{
			switch (nextWalk)
			{
			case up:
				y--;
				break;
			case right:
				x++;
				break;
			case down:
				y++;
				break;
			case left:
				x--;
				break;
			}

			if (x < 0 || x > GAME_WIDTH - 1 || y < 0 || y > GAME_MAP_HEIGHT - 1) break;
			lastWalk = nextWalk;
			expMap[x][y] = '#';

			switch (lastWalk)
			{
			case up:
				switch (randomNumber(0, 9))
				{
				case 0:
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
					nextWalk = up;
					break;
				case 6:
				case 7:
					nextWalk = left;
					break;
				case 8:
				case 9:
					nextWalk = right;
					break;
				}

				break;
			case right:
				switch (randomNumber(0, 9))
				{
				case 0:
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
					nextWalk = right;
					break;
				case 6:
				case 7:
					nextWalk = up;
					break;
				case 8:
				case 9:
					nextWalk = down;
					break;
				}

				break;
			case down:
				switch (randomNumber(0, 9))
				{
				case 0:
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
					nextWalk = down;
					break;
				case 6:
				case 7:
					nextWalk = left;
					break;
				case 8:
				case 9:
					nextWalk = right;
					break;
				}

				break;
			case left:
				switch (randomNumber(0, 9))
				{
				case 0:
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
					nextWalk = left;
					break;
				case 6:
				case 7:
					nextWalk = up;
					break;
				case 8:
				case 9:
					nextWalk = down;
					break;
				}

				break;
			}

			switch (nextWalk)
			{
			case up:
				destination = expMap[x][y - 1];
				break;
			case right:
				destination = expMap[x + 1][y];
				break;
			case down:
				destination = expMap[x][y + 1];
				break;
			case left:
				destination = expMap[x - 1][y];
				break;
			}

		}
	}

	void createDoor(Room * room)
	{
		std::vector<DoorOrientation> door = {};
		int maxDoors = 0;

		switch (room->roomNumber)
		{
		case ROOM_ONE:
			door.push_back(DOOR_RIGHT);
			door.push_back(DOOR_BOTTOM);
			maxDoors = 2;
			break;
		case ROOM_TWO:
			door.push_back(DOOR_RIGHT);
			door.push_back(DOOR_BOTTOM);
			door.push_back(DOOR_LEFT);
			maxDoors = 3;
			break;
		case ROOM_THREE:
			door.push_back(DOOR_BOTTOM);
			door.push_back(DOOR_LEFT);
			maxDoors = 2;
			break;
		case ROOM_FOUR:
			door.push_back(DOOR_TOP);
			door.push_back(DOOR_RIGHT);
			door.push_back(DOOR_BOTTOM);
			maxDoors = 3;
			break;
		case ROOM_FIVE:
			door.push_back(DOOR_TOP);
			door.push_back(DOOR_RIGHT);
			door.push_back(DOOR_BOTTOM);
			door.push_back(DOOR_LEFT);
			maxDoors = 4;
			break;
		case ROOM_SIX:
			door.push_back(DOOR_TOP);
			door.push_back(DOOR_BOTTOM);
			door.push_back(DOOR_LEFT);
			maxDoors = 3;
			break;
		case ROOM_SEVEN:
			door.push_back(DOOR_TOP);
			door.push_back(DOOR_RIGHT);
			maxDoors = 2;
			break;
		case ROOM_EIGHT:
			door.push_back(DOOR_TOP);
			door.push_back(DOOR_RIGHT);
			door.push_back(DOOR_LEFT);
			maxDoors = 3;
			break;
		case ROOM_NINE:
			door.push_back(DOOR_TOP);
			door.push_back(DOOR_LEFT);
			maxDoors = 2;
			break;
		}

		unsigned seed = 0;
		random_shuffle(door.begin(), door.end());

		for (int i = randomNumber(0, maxDoors - 1); i > 0; i--)
		{
			door.pop_back();
		}

		for (auto n : door)
		{
			int x = 0;
			int y = 0;
			Coordinate coord = { 0, 0 };

			switch (n)
			{
			case DOOR_TOP:
				if (room->hasTopDoor) break;
				x = randomNumber(room->x_start + 1, room->x_start + room->x_size - 2);
				y = room->y_start;
				expMap[x][y] = '+';
				coord.x = x;
				coord.y = y;
				doorLocations.push_back(coord);
				room->addDoor(DOOR_TOP, x, y);
				break;
			case DOOR_RIGHT:
				if (room->hasRightDoor) break;
				x = room->x_start + room->x_size - 1;
				y = randomNumber(room->y_start + 1, room->y_start + room->y_size - 2);
				expMap[x][y] = '+';
				coord.x = x;
				coord.y = y;
				doorLocations.push_back(coord);
				room->addDoor(DOOR_RIGHT, x, y);
				break;
			case DOOR_BOTTOM:
				if (room->hasBottomDoor) break;
				x = randomNumber(room->x_start + 1, room->x_start + room->x_size - 2);
				y = room->y_start + room->y_size - 1;
				expMap[x][y] = '+';
				coord.x = x;
				coord.y = y;
				doorLocations.push_back(coord);
				room->addDoor(DOOR_BOTTOM, x, y);
				break;
			case DOOR_LEFT:
				if (room->hasLeftDoor) break;
				x = room->x_start;
				y = randomNumber(room->y_start + 1, room->y_start + room->y_size - 2);
				expMap[x][y] = '+';
				coord.x = x;
				coord.y = y;
				doorLocations.push_back(coord);
				room->addDoor(DOOR_LEFT, x, y);
				break;
			}
		}
	}



	void clearExpMap()
	{
		for (int y = 0; y < GAME_MAP_HEIGHT; y++)
		{
			for (int x = 0; x < GAME_WIDTH; x++)
			{
				expMap[x][y] = ' ';
			}
			expMap[GAME_WIDTH][y] = '\n';
		}
	}

	bool createCorridor(int x, int y, bool visited[GAME_WIDTH + 1][GAME_MAP_HEIGHT], int start_x, int start_y, std::array<direction, 4> dir/*, std::vector<Coordinate> doorLocations*/)
	{
		if (x != start_x || y != start_y)
		{
			if (expMap[x][y] == '#') return true;
			if (expMap[x][y] == '+') return true;
			//{
			//	for (auto coord : doorLocations)
			//	{
			//		if (coord.x == x && coord.y == y) return true;
			//	}

			//}
			if (x >= GAME_WIDTH || y >= GAME_MAP_HEIGHT) return false;
			if (x < 0 || y < 0) return false;
			if (visited[x][y] == true) return false;
			if (expMap[x][y] != ' ') return false;

			visited[x][y] = true;
		}

		for (auto n : dir)
		{
			switch (n)
			{
			case up:
				if (createCorridor(x, y - 1, visited, start_x, start_y, dir))
				{
					if (expMap[x][y] == ' ') expMap[x][y] = '#';
					return true;
				}
				break;
			case right:
				if (createCorridor(x + 1, y, visited, start_x, start_y, dir))
				{
					if (expMap[x][y] == ' ') expMap[x][y] = '#';
					return true;
				}
				break;
			case down:
				if (createCorridor(x, y + 1, visited, start_x, start_y, dir))
				{
					if (expMap[x][y] == ' ') expMap[x][y] = '#';
					return true;
				}
				break;
			case left:
				if (createCorridor(x - 1, y, visited, start_x, start_y, dir))
				{
					if (expMap[x][y] == ' ') expMap[x][y] = '#';
					return true;
				}
				break;
			}

		}
		return false;
	}

	void createNewExpMap()
	{
		numberOfRooms = randomNumber(6, 9);
		unsigned seed = 0;
		random_shuffle(roomNumberList.begin(), roomNumberList.end());

		for (int i = 0; i < numberOfRooms; i++)
		{
			createRoom((RoomNumber)roomNumberList[i]); // to be moved to actual map and not explored map
		}

		for (int i = 0; i < numberOfRooms; i++)
		{
			createDoor(roomList[i]); // to be moved to actual map and not explored map
		}

		for (int i = 0; i < numberOfRooms; i++)
		{
			for (auto d : roomList[i]->doorList)
			{
				bool visited[GAME_WIDTH + 1][GAME_MAP_HEIGHT] = { false };

				//if()
				std::array<direction, 4> dir = { up, down, left, right };

				//createCorridor(start.x, start.y, visited, start.x, start.y, dir/*, doorLocations*/);
			}
		}

		for (int y = 0; y < GAME_MAP_HEIGHT; y++)
		{
			for (int x = 0; x < GAME_WIDTH; x++)
			{
				map[x][y] = expMap[x][y];
			}
			map[GAME_WIDTH][y] = '\n';
		}
	}

	void refreshExpMap()
	{
		for (int y = 0; y < GAME_MAP_HEIGHT; y++)
		{
			for (int x = 0; x < GAME_WIDTH; x++)
			{
				expMap[x][y] = map[x][y];
			}
			expMap[GAME_WIDTH][y] = '\n';
		}
	}

	void makeExpMap()
	{
		mapStr = "";
		for (int y = 0; y < GAME_MAP_HEIGHT; y++)
		{
			for (int x = 0; x < GAME_WIDTH + 1; x++)
			{
				mapStr += expMap[x][y];
			}
		}
	}
};

#endif