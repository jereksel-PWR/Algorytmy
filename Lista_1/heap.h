#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED

typedef struct heap Heap;

typedef struct heap
{
	int *array;
	int size;
} HEAP;

int sort(const void *a, const void *b);

void add(Heap *heap, int a);

bool find(Heap *heap, int a);

#endif
