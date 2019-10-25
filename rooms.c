#include "rooms.h"

struct Room* room(char* description, struct Item* items,
	struct Room* north, struct Room* south,
	struct Room* east, struct Room* west,
	struct Room* up, struct Room* down)
{
	struct Room* room = (struct Room*)malloc(sizeof(struct Room));
	room->description = description;
	room->items = items;
	room->north = north;
	room->south = south;
	room->east = east;
	room->west = west;
	room->up = up;
	room->down = down;
	return room;
}
//functions to set each room direction to another room
void setRoomNorth(struct Room* current, struct Room* other)
{
	current->north = other; 
}
void setRoomSouth(struct Room* current, struct Room* other)
{
	current->south = other;
}
void setRoomEast(struct Room* current, struct Room* other)
{
	current->east = other;
}
void setRoomWest(struct Room* current, struct Room* other)
{
	current->west = other;
}
void setRoomUp(struct Room* current, struct Room* other)
{
	current->up = other;
}
void setRoomDown(struct Room* current, struct Room* other)
{
	current->down = other;
}