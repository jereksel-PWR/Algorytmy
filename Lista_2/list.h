#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED


typedef struct list CList;

typedef struct list
{
	int current_size;
	int max_size;
	void **stuff;  //Array of stuff
} LIST;

CList *list_create();
void list_add(CList *list, void* item);
void* list_get(CList *list, int id);
int list_find(CList *list, void* item);
void list_clear(CList *list);
void list_delete_id(CList *list, int id);

#endif
