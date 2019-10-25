
#include <stdio.h>
#include <stdlib.h>
#include "items.h"
#include "rooms.h"

void printItems(struct Item* item);
void printRoomInfo(struct Room* room, _Bool canMove);

int main(void)
{
	//set up all the rooms and items
	struct Item* hallItems = item("picture frame", "picture frame", item("mirror", "mirror", NULL));
	struct Room* masterBedroom = room("Master Bedroom", item("lantern", "used to illuminate the surrounding environment to move around", NULL) , NULL, NULL, NULL, NULL, NULL, NULL);
	struct Room* bathroom = room("Bathroom", item("hand soap", "hand soap", item("towel", "towel", NULL)) , NULL, NULL, NULL, NULL, NULL, NULL);
	struct Room* guestBedroom = room("Guest Bedroom", item("toolkit", "used to repair the electrical box", NULL) , NULL, NULL, NULL, NULL, NULL, NULL);
	struct Room* hallway1 = room("Hallway", hallItems , NULL, NULL, NULL, NULL, NULL, NULL);
	struct Room* hallway2 = room("Hallway", hallItems, NULL, NULL, NULL, NULL, NULL, NULL);
	struct Room* kitchen = room("Kitchen", item("car keys", "used to drive the car and escape the house", NULL), NULL, NULL, NULL, NULL, NULL, NULL);
	struct Room* livingRoom = room("Living Room", item("remote", "remote", NULL) , NULL, NULL, NULL, NULL, NULL, NULL);
	struct Room* elevator1 = room("Elevator on the first floor", item(NULL, NULL, NULL) , NULL, NULL, NULL, NULL, NULL, NULL);
	struct Room* garage = room("Garage", item("garage opener", "used to open the garage", NULL), NULL, NULL, NULL, NULL, NULL, NULL);
	struct Room* elevator2 = room("Elevator on the second floor", item(NULL, NULL, NULL) , NULL, NULL, NULL, NULL, NULL, NULL);
	struct Room* diningRoom = room("Dining Room", item("apple", "apple", NULL), NULL, NULL, NULL, NULL, NULL, NULL);
	
	//link all the rooms together
	setRoomNorth(bathroom, masterBedroom);
	setRoomSouth(masterBedroom, bathroom);
	setRoomEast(masterBedroom, guestBedroom);
	setRoomWest(guestBedroom, masterBedroom);
	setRoomNorth(masterBedroom, hallway1);
	setRoomNorth(guestBedroom, hallway2);
	setRoomSouth(hallway1, masterBedroom);
	setRoomSouth(hallway2, guestBedroom);
	setRoomWest(hallway1, elevator2);
	setRoomEast(elevator2, hallway1);
	setRoomSouth(elevator1, livingRoom);
	setRoomNorth(livingRoom, elevator1);
	setRoomEast(livingRoom, diningRoom);
	setRoomWest(diningRoom, livingRoom);
	setRoomEast(diningRoom, kitchen);
	setRoomWest(kitchen, diningRoom);
	setRoomSouth(livingRoom, garage);
	setRoomNorth(garage, livingRoom);
	setRoomEast(hallway1, hallway2);
	setRoomWest(hallway2, hallway1);

	//setup game variables
	_Bool gameOver = 0;
	_Bool garageOpened = 0;
	_Bool canMove = 0;
	_Bool succ = 0;
	//player inventory
	struct Item* inventory = item(NULL, NULL, NULL); //player's items
	int numItems = 0;
	//player starts in master bedroom
	struct Room* currRoom = masterBedroom;

	//setup input variables
	char* input = NULL;
	char* command = NULL;
	char* object = NULL; //item or room string
	int bufSize = 32;

	//instructions
	printf("You are trapped in a haunted house.\nThe only way to leave is with the car through the garage.\nNavigate your way to solve the puzzles and escape the house.\n\nYou can use the following commands:\nlook - get information about the room you are in\ninventory - see the items you have\ntake (item)- pick up an item\ndrop (item) - drop an item\nuse (item) - use an item\ngo (direction) - move in a direction\n");
	
	while (!gameOver)
	{
		//get input line
		printf("\n--> ");
		getline(&input, &bufSize, stdin);
		printf("\n");
		//if input has two arguments
		if (strchr(input, ' '))
		{
			command = strtok(input, " ");
		}
		//only one argument (no space)
		else
		{
			command = strtok(input, "\n");
		}
		if (command != NULL)
		{
			object = strtok(NULL, "\n");
			if (!strcmp(command, "go"))
			{
				if (object != NULL)
				{
					if (canMove)
					{
						//go through every direction and make the appropriate move
						if (!strcmp(object, "north"))
						{
							if (currRoom->north != NULL) //make sure player can move here
							{
								currRoom = (currRoom->north); //set current room pointer to the north room
							}
							else
							{
								printf("You cannot move here\n");
							}
						}
						else if (!strcmp(object, "south"))
						{
							if (currRoom->south != NULL)
							{
								currRoom = (currRoom->south);
							}
							else
							{
								printf("You cannot move here\n");
							}
						}
						else if (!strcmp(object, "east"))
						{
							if (currRoom->east != NULL)
							{
								currRoom = (currRoom->east);
							}
							else
							{
								printf("You cannot move here\n");
							}
						}
						else if (!strcmp(object, "west"))
						{
							if (currRoom->west != NULL)
							{
								currRoom = (currRoom->west);
								if (currRoom == elevator2)
								{
									printf("The elevator is broken. Fix it with the toolkit\n");
								}
							}
							else
							{
								printf("You cannot move here\n");
							}
						}
						else if (!strcmp(object, "up"))
						{
							if (currRoom->up != NULL)
							{
								currRoom = (currRoom->up);
							}
							else
							{
								printf("You cannot move here\n");
							}
						}
						else if (!strcmp(object, "down"))
						{
							if (currRoom->down != NULL)
							{
								currRoom = (currRoom->down);
							}
							else
							{
								printf("You cannot move here\n");
							}
						}
						else
						{
							printf("Illegal input\n");
						}
						printRoomInfo(currRoom, canMove);
					}
					else
					{
						//player tried to move without the lantern
						printf("You cannot move, it is pitch black\n");
					}
				}
				else
				{
					printf("Illegal input\n");
				}
			}
			else if (!strcmp(command, "use"))
			{
				//make approprite commands for every item we can use
				if (object != NULL)
				{
					//player has to use garage opener in the garage
					if (!strcmp(object, "garage opener") && currRoom == garage)
					{
						garageOpened = 1;
						printf("You opened the garage!\n");
					}
					//player wins if used key in the garage after opening the garage
					else if (!strcmp(object ,"car keys") && garageOpened && currRoom == garage)
					{
						gameOver = 1;
						printf("Good job, you won!\n");
					}
					//player fixed elevator if he used the toolkit in the elevator
					else if (!strcmp(object, "toolkit") && currRoom == elevator2)
					{
						setRoomDown(elevator2, elevator1); //link the two floors with the elevator after player fixed it
						setRoomUp(elevator1, elevator2);
						printf("You fixed the elevator\n");
					}
					else
					{
						printf("You cannot use this item here\n");
					}
				}
				else
				{
					printf("Illegal input\n");
				}
			}
			else if (!strcmp(command, "take"))
			{
				if (object != NULL)
				{
					if (numItems < 5)
					{
						succ = 1;
						inventory = itemTake(currRoom->items, object, inventory, &succ);
						//only if itemTake ran successfully (item is in the room)
						if (succ)
						{
							numItems++;
							printf("Obtained %s\n", object);
							//unlock player movement
							if (!strcmp(object, "lantern"))
							{
								canMove = 1;
								printf("You can now move around\n");
							}
							
						}
					}
					else
					{
						//can only hold 5 items
						printf("Inventory is full\n");
					}
				}
				else
				{
					printf("Illegal input\n");
				}
			}
			else if (!strcmp(command, "drop"))
			{
				if (object != NULL)
				{
					succ = 1;
					currRoom->items = itemDrop(object, inventory, currRoom->items, &succ);
					//only if itemDrop ran successfully (item is in inventory)
					if (succ)
					{
						numItems--;
						if (!strcmp(object, "lantern"))
						{
							//restrict player moevment if dropped lantern
							canMove = 0;
						}
						printf("Dropped %s\n", object);
					}
				}
				else
				{
					printf("Illegal input\n");
				}
			}
			else if (!strcmp(command, "look"))
			{
				printRoomInfo(currRoom, canMove);
			}
			else if (!strcmp(command, "inventory"))
			{
				printItems(inventory);
			}
			else
			{
				printf("Illegal input\n");
			}
		}
	}

	//free up all the pointers
	free(masterBedroom);
	free(guestBedroom);
	free(hallway1);
	free(hallway2);
	free(bathroom);
	free(elevator2);
	free(elevator1);
	free(livingRoom);
	free(garage);
	free(kitchen);
	free(diningRoom);
	free(inventory);
	//end program after freeing pointer
	return 0;
}
void printItems(struct Item* item)
{
	//print all the items in the list recursively
	if (item != NULL)
	{
		if (item->name != NULL)
		{
			printf("%s\n", item->name);
			printItems(item->next);
		}
	}
}
void printRoomInfo(struct Room* room, _Bool canMove)
{
	printf("You are in the %s\nThe items in this room are:\n", room->description);
	printItems(room->items);
	printf("\n%s", "You can move ");
	_Bool nowhere = 0;
	//go through every direction and print available moves
	if (canMove)
	{
		if (room->north != NULL) //make sure player can move here
		{
			printf("north, ");
			nowhere = 1;
		}
		if (room->south != NULL)
		{
			printf("south, ");
			nowhere = 1;
		}
		if (room->east != NULL)
		{
			printf("east, ");
			nowhere = 1;
		}
		if (room->west != NULL)
		{
			printf("west, ");
			nowhere = 1;
		}
		if (room->up != NULL)
		{
			printf("up, ");
			nowhere = 1;
		}
		if (room->down != NULL)
		{
			printf("down");
			nowhere = 1;
		}
		if (!nowhere)
		{
			printf("nowhere");
		}
		printf("\n");
	}
	else
	{
		//cannot move anywhere
		printf("nowhere\n");
	}
}
