#ifndef ROOMS_H
#define ITEMS_H

#include <stdio.h>
#include <stdlib.h>

struct Room
{
	char* description;
	struct Item* items;
	struct Room* north;
	struct Room* south;
	struct Room* east;
	struct Room* west;
	struct Room* up;
	struct Room* down;
};

struct Room* room(char* description, struct Item* items,
	struct Room* north, struct Room* south,
	struct Room* east, struct Room* west,
	struct Room* up, struct Room* down);
//link room directions
void setRoomNorth(struct Room* current, struct Room* other);
void setRoomSouth(struct Room* current, struct Room* other);
void setRoomEast(struct Room* current, struct Room* other);
void setRoomWest(struct Room* current, struct Room* other);
void setRoomUp(struct Room* current, struct Room* other);
void setRoomDown(struct Room* current, struct Room* other);

#endif /* rooms.h*/