#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "heap.h"

void add(Heap *heap, int a)
{
	heap->array[heap->size] = a;
	heap->size++;
	qsort(heap->array, heap->size, sizeof(int), sort);
}

int sort(const void *a, const void *b)
{
	return (*(int *) a - *(int *) b);
}


bool find(Heap *heap, int a)
{

	int left = 0;
	int right = (heap->size);

	while (left <= right)
	{
		int srodek = (left + right) / 2;

		if (heap->array[srodek] == a)
		{
			return true;
		}

		if (heap->array[srodek] < a)
		{
			left = srodek + 1;
		}
		else
		{
			right = srodek - 1;
		}
	}

	return false;
}
