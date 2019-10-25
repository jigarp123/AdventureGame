#ifndef ITEMS_H
#define ITEMS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Item
{
	char* name;
	char* description;
	struct Item* next;
};

//make new item
struct Item* item(char* name, char* description, struct Item* next);
char* itemName(struct Item* item);
char* itemDescription(struct Item* item);
struct Item* itemNext(struct Item* item);
//remove an item from a list
struct Item* itemRemove(char* name, struct Item* head, struct Item* prev);
//take an item from a room
struct Item* itemTake(struct Item* roomItems, char* name, struct Item* items, _Bool *succs);
//drop an item in a room
struct Item *itemDrop(char *name, struct Item* items, struct Item* roomItems, _Bool *succ);

#endif /* items.h*/


