#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "avl.h"

//#define DEBUG

int main(int argc, char *argv[])
{
	Tree *tree = create_tree();

	if (argc != 2)
	{
		printf("usage: %s filename\n", argv[0]);
		return 0;
	}

	FILE *fp = fopen(argv[1], "r");

	if (fp == 0)
	{
		printf("READ ERROR\n");
		return 0;
	}

	int i = 0;
	int end;
	fscanf(fp, "%d", &end);


	while (i != end)
	{
		char *action = malloc(sizeof(char) * 50);
		int number;

		fscanf(fp, "%s", action);

		if (strcmp(action, "insert") == 0)
		{
			fscanf(fp, "%d", &number);
			insert(tree, number);
			i++;
		}
		else if (strcmp(action, "delete") == 0)
		{
			fscanf(fp, "%d", &number);
			delete(tree, number);
			i++;
		}
		else if (strcmp(action, "find") == 0)
		{
			fscanf(fp, "%d", &number);
			find(tree, number);
			i++;
		}
		else if (strcmp(action, "min") == 0)
		{
			min(tree);
			i++;
		}
		else if (strcmp(action, "max") == 0)
		{
			max(tree);
			i++;
		}
		else if (strcmp(action, "inorder") == 0)
		{
			inorder(tree);
			i++;
		}
	}

#ifdef DEBUG
	printTree(tree);
#endif

	return 0;
}