#pragma once
#ifndef ROOM
#define ROOM

#include "Helper.h"


class Room
{
public:

	int roomNumber = 0;
	int x_start = 0;
	int y_start = 0;
	int x_size = 0;
	int y_size = 0;

	bool hasTopDoor = false;
	bool hasRightDoor = false;
	bool hasBottomDoor = false;
	bool hasLeftDoor = false;

	std::vector<door> doorList = {};

	Room(RoomNumber room, int x_start, int y_start, int x_size, int y_size)
	{
		this->roomNumber = room;
		this->x_size = x_size;
		this->y_size = y_size;

		switch (room)
		{
		case ROOM_ONE:
			this->x_start = x_start;
			this->y_start = y_start;
			break;
		case ROOM_TWO:
			this->x_start = x_start + 27;
			this->y_start = y_start;
			break;
		case ROOM_THREE:
			this->x_start = x_start + 54;
			this->y_start = y_start;
			break;
		case ROOM_FOUR:
			this->x_start = x_start;
			this->y_start = y_start + 8;
			break;
		case ROOM_FIVE:
			this->x_start = x_start + 27;
			this->y_start = y_start + 8;
			break;
		case ROOM_SIX:
			this->x_start = x_start + 54;
			this->y_start = y_start + 8;
			break;
		case ROOM_SEVEN:
			this->x_start = x_start;
			this->y_start = y_start + 16;
			break;
		case ROOM_EIGHT:
			this->x_start = x_start + 27;
			this->y_start = y_start + 16;
			break;
		case ROOM_NINE:
			this->x_start = x_start + 54;
			this->y_start = y_start + 16;
			break;
		}
	};

	bool addDoor(DoorOrientation ori, int x_loc, int y_loc)
	{
		door d = { ori, x_loc, y_loc };
		switch (ori)
		{
		case DOOR_TOP:
			this->hasTopDoor = true;
			doorList.push_back(d);
			break;
		case DOOR_RIGHT:
			this->hasRightDoor = true;
			doorList.push_back(d);
			break;
		case DOOR_BOTTOM:
			this->hasBottomDoor = true;
			doorList.push_back(d);
			break;
		case DOOR_LEFT:
			this->hasLeftDoor = true;
			doorList.push_back(d);
			break;
		}

		return true;
	}
};

#endif
