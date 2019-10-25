#include "items.h"

struct Item* item(char* name, char* description, struct Item* next)
{
	struct Item* itemPtr = (struct Item*)malloc(sizeof(struct Item));
	itemPtr->name = name;
	itemPtr->description = description;
	itemPtr->next = next;
	return itemPtr;
}

char* itemName(struct Item* item)
{
	return item->name;
}
char* itemDescription(struct Item* item)
{
	return item->description;
}
struct Item* itemNext(struct Item* item)
{
	return item->next;
}

struct Item* itemRemove(char* name, struct Item* head, struct Item* prev)
{
	//make sure there is no null pointer
	if (head != NULL)
	{
		//if item is found
		if (!strcmp(name, itemName(head)))
		{
			//if this is the first item in the list
			if (prev == NULL)
			{
				//if list is empty
				if (head->name == NULL)
				{
					return NULL;
				}
				//otherwise create a new item to return the remove item
				struct Item* ret = (struct Item*)malloc(sizeof(struct Item));
				ret->name = head->name;
				ret->description = head->description;
				ret->next = NULL;
				//if this is the only item, set it to an empty list
				if (itemNext(head) == NULL)
				{
					*head = *item(NULL, NULL, NULL);
				} 
				else
				{
					*head = *itemNext(head);
				}
				//return removed item
				return ret;
			}
			else
			{
				//skip this item that is referenced by the parent pointer
				prev->next = itemNext(head);
				return head;
			}

		}
		else
		{
			//recursively go through every item in the list
			return itemRemove(name, itemNext(head), head);
		}
	}
	return NULL;
}
struct Item *itemTake(struct Item* roomItems, char *name, struct Item* items, _Bool *succ)
{
	struct Item *item = itemRemove(name, roomItems, NULL);
	//if item was not found
	if (item == NULL)
	{
		printf("Illegal input\n");
		*succ = 0;
		return items;
	}
	if (items->name == NULL)
	{
		return item;
	}
	//add this item to the inventory and return this new list
	(item->next) = items;
	return item;
}
struct Item *itemDrop(char *name, struct Item* items, struct Item* roomItems, _Bool* succ)
{
	struct Item *item = itemRemove(name, items, NULL);
	//if item was not found
	if (item == NULL)
	{
		printf("Illegal input\n");
		*succ = 0;
		return roomItems;
	}
	if (roomItems->name == NULL)
	{
		return item;
	}
	//add this item to the room and return the new room item list
	item->next = roomItems;
	return item;
}