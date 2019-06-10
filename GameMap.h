#pragma once
#ifndef GAMEMAP
#define GAMEMAP
#include "Helper.h"
#include "Room.h"
#include "UnitsAndItems.h"


// Game dimension constants
const int GAME_WIDTH = 80;
const int GAME_HEIGHT = 25;
const int GAME_MAP_HEIGHT = 23;

class GameMap
{
public:

	// holds the base map that is created (rooms, corridors, stairs, rest area)
	char map[GAME_WIDTH + 1][GAME_MAP_HEIGHT] = { 0 };

	// holds which areas are explored
	bool isExplored[GAME_WIDTH][GAME_MAP_HEIGHT] = { false };

	// holds the areas to be displayed if explored
	char expMap[GAME_WIDTH + 1][GAME_MAP_HEIGHT] = { 0 };	// exp -> explored
	
	// holds the string of the map to be passed to main
	std::string mapStr = "";

	char destination = ' ';
	bool newFloor = true;
	Coordinate stairs_loc;
	Coordinate restArea_loc;

	// holds an array room numbers to shuffle and randomize
	std::array<int, 9> roomNumberList{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	// holds the number of rooms to create
	int numberOfRooms = 0;

	// holds a vector of rooms that have been created
	std::vector<Room*> roomList = {};

	// holds the location corrdinates of all the doors on the floor
	std::vector<Coordinate> doorLocations;

	GameMap() 
	{
		Init();
	};

	~GameMap() {};

	// given room info, draws the room on the map
	bool drawRoom(Room * room)
	{
		for (int y = room->y_start; y < room->y_start + room->y_size; y++)
		{
			for (int x = room->x_start; x < (room->x_start + room->x_size) && y == room->y_start; x++)
			{
				map[x][y] = '-';
			}

			for (int x = room->x_start; x < (room->x_start + room->x_size) && y > room->y_start && y < (room->y_start + room->y_size - 1); x++)
			{
				if (x == room->x_start || x == (room->x_start + room->x_size - 1))
				{
					map[x][y] = '|';
				}
				else
				{
					map[x][y] = '.';
				}

			}

			for (int x = room->x_start; x < (room->x_start + room->x_size) && y == (room->y_start + room->y_size - 1); x++)
			{
				map[x][y] = '-';
			}
		}
		return true;
	}

	// creates a room given a number 1-9 where the map is divided into a 3x3 grid to place rooms:
	// 1 : top-right
	// 2 : top-center
	// 3 : top-left 
	// 4 : center-right
	// 5 : center      
	// 6 : center-left 
	// 7 : bottom-right
	// 8 : bottom-center
	// 9 : bottom-left 
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

	// given the type of room, creates doors on the rooms:
	// corner rooms are given 2 doors,
	// middle edge rooms are given 3 doors,
	// and center is given 4 doors.
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
				map[x][y] = '+';
				coord.x = x;
				coord.y = y;
				doorLocations.push_back(coord);
				room->addDoor(DOOR_TOP, x, y);
				break;
			case DOOR_RIGHT:
				if (room->hasRightDoor) break;
				x = room->x_start + room->x_size - 1;
				y = randomNumber(room->y_start + 1, room->y_start + room->y_size - 2);
				map[x][y] = '+';
				coord.x = x;
				coord.y = y;
				doorLocations.push_back(coord);
				room->addDoor(DOOR_RIGHT, x, y);
				break;
			case DOOR_BOTTOM:
				if (room->hasBottomDoor) break;
				x = randomNumber(room->x_start + 1, room->x_start + room->x_size - 2);
				y = room->y_start + room->y_size - 1;
				map[x][y] = '+';
				coord.x = x;
				coord.y = y;
				doorLocations.push_back(coord);
				room->addDoor(DOOR_BOTTOM, x, y);
				break;
			case DOOR_LEFT:
				if (room->hasLeftDoor) break;
				x = room->x_start;
				y = randomNumber(room->y_start + 1, room->y_start + room->y_size - 2);
				map[x][y] = '+';
				coord.x = x;
				coord.y = y;
				doorLocations.push_back(coord);
				room->addDoor(DOOR_LEFT, x, y);
				break;
			}
		}
	}

	
	// choose random room
	// place randomly in that room 
	bool placeStairs()
	{
		int x_start = this->roomList[2]->x_start;
		int y_start = this->roomList[2]->y_start;

		int x_size = this->roomList[2]->x_size;
		int y_size = this->roomList[2]->y_size;

		int x_pos = randomNumber(x_start + 1, x_start + x_size - 2);
		int y_pos = randomNumber(y_start + 1, y_start + y_size - 2);

		if (this->map[x_pos][y_pos] == '.')
		{
			this->map[x_pos][y_pos] = '%';
			stairs_loc.x = x_pos;
			stairs_loc.y = y_pos;
			return true;
		}

		return false;
	}

	// place rest area on map
	// choose random room
	// place randomly in that room 
	bool placeRestArea()
	{
		// checks if to place rest area on map 25% chance
		if (randomNumber(1, 4) != 1)
		{
			restArea_loc.x = 0;
			restArea_loc.y = 0;
			return false;
		}

		int x_start = this->roomList[5]->x_start;
		int y_start = this->roomList[5]->y_start;

		int x_size = this->roomList[5]->x_size;
		int y_size = this->roomList[5]->y_size;

		int x_pos = randomNumber(x_start + 1, x_start + x_size - 2);
		int y_pos = randomNumber(y_start + 1, y_start + y_size - 2);

		if (this->map[x_pos][y_pos] == '.')
		{
			this->map[x_pos][y_pos] = '!';
			restArea_loc.x = x_pos;
			restArea_loc.y = y_pos;
			return true;
		}

		return false;
	}

	// clears the map with ' ' (space characters)
	void clearMap()
	{
		for (int y = 0; y < GAME_MAP_HEIGHT; y++)
		{
			for (int x = 0; x < GAME_WIDTH; x++)
			{
				map[x][y] = ' ';
			}
			map[GAME_WIDTH][y] = '\n';
		}
	}

	// check if room player will be spawned in can reach the room the stairs are spawned in.
	bool isMapValid(int start_x, int start_y, bool visited[GAME_WIDTH + 1][GAME_MAP_HEIGHT], int end_x, int end_y)
	{
		if (map[start_x][start_y] == '.' || map[start_x][start_y] == '+' || map[start_x][start_y] == '#' )
		{
			if (start_x == end_x && start_y == end_y) return true;
			if (start_x >= GAME_WIDTH - 1 || start_y >= GAME_MAP_HEIGHT - 1) return false;
			if (start_x < 1 || start_y < 1) return false;
			if (visited[start_x][start_y] == true) return false;
		}
		else return false;

		visited[start_x][start_y] = true;

		std::array<Direction, 4> dir = { down, up, left, right };

		for (auto n : dir)
		{
			switch (n)
			{
			case up:
				if (isMapValid(start_x, start_y - 1, visited, end_x, end_y))
				{
					return true;
				}
				break;
			case right:
				if (isMapValid(start_x + 1, start_y, visited, end_x, end_y))
				{
					return true;
				}
				break;
			case down:
				if (isMapValid(start_x, start_y + 1, visited, end_x, end_y))
				{
					return true;
				}
				break;
			case left:
				if (isMapValid(start_x - 1, start_y, visited, end_x, end_y))
				{
					return true;
				}
				break;
			}
		}
		return false;
	}

	// creates corridors with a mix of flood fill and drunken walker algorithms.
	bool createCorridor(int x, int y, bool visited[GAME_WIDTH][GAME_MAP_HEIGHT], int start_x, int start_y, std::array<Direction, 10> dir, Direction lastMove)
	{
		if (x != start_x || y != start_y)
		{
			if (map[x][y] == '#') return true;
			if (map[x][y] == '+') return true;
			if (x >= GAME_WIDTH - 1 || y >= GAME_MAP_HEIGHT - 1) return false;
			if (x < 1 || y < 1) return false;
			if (visited[x][y] == true) return false;
			if (map[x][y] != ' ') return false;

			visited[x][y] = true;
		}

		// drunken walker random movement, where last move is prefered movement
		switch (lastMove)
		{
		case DOOR_TOP:
			dir = { up, up, up, up, up, up, up, up, left, right };
			break;
		case DOOR_RIGHT:
			dir = { right, right, right, right, right, right, right, right, up, down };
			break;
		case DOOR_BOTTOM:
			dir = { down, down, down, down, down, down, down, down, left, right };
			break;
		case DOOR_LEFT:
			dir = { left, left, left, left, left, left, left, left, up, down };
			break;
		}

		random_shuffle(dir.begin(), dir.end());
		lastMove = dir.front();

		// flood fill algorithm to recursively call when desitnation is reached
		for (auto n : dir)
		{
			switch (n)
			{
			case up:
				if (createCorridor(x, y - 1, visited, start_x, start_y, dir, up))
				{
					if (map[x][y] == ' ') map[x][y] = '#';
					return true;
				}
				break;
			case right:
				if (createCorridor(x + 1, y, visited, start_x, start_y, dir, right))
				{
					if (map[x][y] == ' ') map[x][y] = '#';
					return true;
				}
				break;
			case down:
				if (createCorridor(x, y + 1, visited, start_x, start_y, dir, down))
				{
					if (map[x][y] == ' ') map[x][y] = '#';
					return true;
				}
				break;
			case left:
				if (createCorridor(x - 1, y, visited, start_x, start_y, dir, left))
				{
					if (map[x][y] == ' ') map[x][y] = '#';
					return true;
				}
				break;
			}
		}
		return false;
	}

	// creates a new map to be placed into map double char array
	void createNewMap()
	{
		while(true)
		{
			Init();
			roomList.clear();
			
			// creates between 6 - 9 rooms per map
			numberOfRooms = randomNumber(6, 9);
			unsigned seed = 0;

			// randomizes where rooms to create
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

					std::array<Direction, 10> dir;
					switch (d.ori)
					{
					case DOOR_TOP:
						dir = { up, up, up, up, up, up, up, up, left, right };
						break;
					case DOOR_RIGHT:
						dir = { right, right, right, right, right, right, right, right, up, down };
						break;
					case DOOR_BOTTOM:
						dir = { down, down, down, down, down, down, down, down, left, right };
						break;
					case DOOR_LEFT:
						dir = { left, left, left, left, left, left, left, left, up, down };
						break;
					}

					random_shuffle(dir.begin(), dir.end());
					Direction lastMove = dir.front();

					createCorridor(d.x_loc, d.y_loc, visited, d.x_loc, d.y_loc, dir, lastMove);
				}
			}

			placeStairs();
			placeRestArea();

			bool visited[GAME_WIDTH][GAME_MAP_HEIGHT] = { false };

			int start_x = randomNumber(roomList.front()->x_start + 1, roomList.front()->x_start + roomList.front()->x_size - 2);
			int start_y = randomNumber(roomList.front()->y_start + 1, roomList.front()->y_start + roomList.front()->y_size - 2);

			int end_x = randomNumber(roomList[2]->x_start + 1, roomList[2]->x_start + roomList[2]->x_size - 2);
			int end_y = randomNumber(roomList[2]->y_start + 1, roomList[2]->y_start + roomList[2]->y_size - 2);

			if (isMapValid(start_x, start_y, visited, end_x, end_y)) break;
		} 
	}

	// updates the Explored Map if player has discovered new areas
	void refreshExpMap()
	{
		for (int y = 0; y < GAME_MAP_HEIGHT; y++)
		{
			for (int x = 0; x < GAME_WIDTH; x++)
			{
				if (isExplored[x][y]) 
				{
					expMap[x][y] = map[x][y];
				}
				else
				{
					expMap[x][y] = ' ';
				}
			}
			expMap[GAME_WIDTH][y] = '\n';
		}
	}

	// turns the ExpMap double char array into a string to pass to main
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

	// recursive function to explore the room when the player walks into it
	void exploreRoom(int start_x, int start_y)
	{
		if (start_x >= GAME_WIDTH || start_y >= GAME_MAP_HEIGHT) return;
		if (start_x < 0 || start_y < 0) return;
		if (isExplored[start_x][start_y] == true) return;	
		if (map[start_x][start_y] == ' ' || map[start_x][start_y] == '#') return;

		isExplored[start_x][start_y] = true;

		if (map[start_x][start_y] == '-') return;

		exploreRoom(start_x - 1, start_y - 1);
		exploreRoom(start_x - 1, start_y);
		exploreRoom(start_x - 1, start_y + 1);
		exploreRoom(start_x, start_y - 1);
		exploreRoom(start_x, start_y + 1);
		exploreRoom(start_x + 1, start_y - 1);
		exploreRoom(start_x + 1, start_y);
		exploreRoom(start_x + 1, start_y + 1);		
	}

	// checks the players immediate surrounding to explore
	bool checkSurrounding(char surr)
	{
		if (surr == '#' || surr == '+' || surr == '-' || surr == '|') return true;
		else return false;
	}

	// explores the players immediate surrounding when traversing the corridors
	void exploreSurrounding(int start_x, int start_y)
	{
		isExplored[start_x + 1][start_y + 1] ? true : isExplored[start_x + 1][start_y + 1] = checkSurrounding(map[start_x + 1][start_y + 1]);
		isExplored[start_x + 1][start_y] ? true : isExplored[start_x + 1][start_y] = (checkSurrounding(map[start_x + 1][start_y]) || map[start_x + 1][start_y] == '.' || map[start_x + 1][start_y] == '%' || map[start_x + 1][start_y] == '!');
		isExplored[start_x + 1][start_y - 1] ? true : isExplored[start_x + 1][start_y - 1] = checkSurrounding(map[start_x + 1][start_y - 1]);
		isExplored[start_x][start_y + 1] ? true : isExplored[start_x][start_y + 1] = (checkSurrounding(map[start_x][start_y + 1]) || map[start_x][start_y + 1] == '.' || map[start_x][start_y + 1] == '%' || map[start_x][start_y + 1] == '!');
		isExplored[start_x][start_y - 1] ? true : isExplored[start_x][start_y - 1] = (checkSurrounding(map[start_x][start_y - 1]) || map[start_x][start_y - 1] == '.' || map[start_x][start_y - 1] == '%' || map[start_x][start_y - 1] == '!');
		isExplored[start_x - 1][start_y + 1] ? true : isExplored[start_x - 1][start_y + 1] = checkSurrounding(map[start_x - 1][start_y + 1]);
		isExplored[start_x - 1][start_y] ? true : isExplored[start_x - 1][start_y] = (checkSurrounding(map[start_x - 1][start_y]) || map[start_x - 1][start_y] == '.' || map[start_x - 1][start_y] == '%' || map[start_x - 1][start_y] == '!');
		isExplored[start_x - 1][start_y - 1] ? true : isExplored[start_x - 1][start_y - 1] = checkSurrounding(map[start_x - 1][start_y - 1]);
	}

	// method to handle players exploration of the map
	void explore(int player_x, int player_y)
	{
		if (map[player_x][player_y] == '.' || map[player_x][player_y] == '%')
		{
			exploreRoom(player_x + 1, player_y);
			exploreRoom(player_x - 1, player_y);
			exploreRoom(player_x, player_y + 1);
			exploreRoom(player_x, player_y - 1);
		}

		if (map[player_x][player_y] == '#' || map[player_x][player_y] == '+')
		{
			exploreSurrounding(player_x, player_y);
		}
	}

	// initalizes the GameMap various arrays to be used to create a new map
	void Init()
	{
		clearMap();
		
		for (int y = 0; y < GAME_MAP_HEIGHT; y++)
		{
			for (int x = 0; x < GAME_WIDTH; x++)
			{
				expMap[x][y] = map[x][y];
				isExplored[x][y] = false;
			}
			expMap[GAME_WIDTH][y] = '\n';
		}
	}
};

#endif