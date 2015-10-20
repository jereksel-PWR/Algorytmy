#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "sposobwydawania.h"

#define STEP 1

CList *list_create()
{
	CList *list = malloc(sizeof(CList));

	list->stuff = malloc(sizeof(void *) * STEP);
	list->current_size = 0;
	list->max_size = STEP;
	return list;
}

void list_add(CList *list, void *item)
{
	if (list->current_size + 1 == list->max_size)
	{
		list->max_size = list->max_size + STEP;
		list->stuff = realloc(list->stuff, sizeof(void *) * list->max_size);
	}

	list->stuff[list->current_size] = item;
	list->current_size++;
}

int list_find(CList *list, void *item)
{
	for (int i = 0; i < list->current_size; i++)
	{
		if (list_get(list, i) == item)
		{
			return i;
		}
	}

	return -1;
}


void *list_get(CList *list, int id)
{
	return list->stuff[id];
}

void list_clear(CList *list)
{

	//WIEM, ŻE TAM SĄ OBIEKTY "WYDAWANIE"
	for (int i = 0; i < list->current_size; i++)
	{
		//printf("Czyszczenie właściwe\n");
		Wydawanie *wydawanie1 = list->stuff[i];
		free(wydawanie1->ilosc_monet);
		free(wydawanie1);
	}

	list->current_size = 0;
	list->max_size = STEP;
	list->stuff = realloc(list->stuff, sizeof(void *) * list->max_size);

}


void list_delete_item()
{
//TODO: IMPLEMENT
}

void list_delete_id(CList *list, int id)
{

	if (id >= list->current_size)
	{
		return;
	}

	//WIEM, ŻE TAM SĄ OBIEKTY "WYDAWANIE"
	Wydawanie *wydawanie = list->stuff[id];

	free(wydawanie->ilosc_monet);
	free(wydawanie);

	for (int i = id; i < list->current_size; i++)
	{
		list->stuff[i] = list->stuff[i + 1];
	}

	list->current_size--;

}