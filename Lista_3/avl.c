#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "avl.h"

#define new(x) malloc(sizeof(x))
#define maxInt(a, b) (((a)>(b))?(a):(b))

int height(Node *node);

void balanceLeft(Node *node);

int balance(Node *node);

void balanceRight(Node *node);

Node *findPrivate(Node *node, int item, bool refreshHeight);

void fixTree(Node *node);

Node *minPrivate(Node *node, bool refreshHeight);

Node *maxPrivate(Node *node);

void print_t(Node *tree);

char **twoDimentialArray(int x, int y);

Node *newNode()
{
	Node *node = new(Node);
	node->left = NULL;
	node->right = NULL;
	node->height = 1;
	node->heightRebuild = false;
	return node;
}


Tree *create_tree()
{
	Tree *tree = new(Tree);
	tree->firstNode = NULL;
	return tree;
}

void printNode(Node *node)
{

	if (node == NULL)
		return;


	printNode(node->left);
	printf("%d ", node->data);
	printNode(node->right);

}

void insert(Tree *tree, int item)
{
	//Puste drzewo
	if (tree->firstNode == NULL)
	{
		tree->firstNode = newNode();
		tree->firstNode->data = item;
		tree->firstNode->parent = NULL;
		return;
	}

	Node *node = tree->firstNode;
	node->heightRebuild = true;

	//Szukamy gdzie wstawić nasz item
	while (true)
	{
		node->heightRebuild = true;
		if (item == node->data)
		{
			break;
		}


		if (item > node->data)
		{
			if (node->right != NULL)
			{
				node = node->right;
			}
			else
			{
				node->right = newNode();
				node->right->parent = node;
				node->right->data = item;
				break;
			}
		}
		else
		{
			if (node->left != NULL)
			{
				node = node->left;
			}
			else
			{
				node->left = newNode();
				node->left->parent = node;
				node->left->data = item;
				break;
			}
		}
	}

	fixTree(node);
}

void inorder(Tree *tree)
{

	//Puste drzewo
	if (tree->firstNode == NULL)
	{
		printf("\n");
		return;
	}

	Node *node = tree->firstNode;

	printNode(node);
	printf("\n");
}


int balance(Node *node)
{
	if (node->heightRebuild)
	{
		node->height = 1 + maxInt(height(node->right), height(node->left));
	}

	return height(node->left) - height(node->right);
}

int height(Node *node)
{
	if (node == NULL)
		return 0;

	if (node->heightRebuild)
	{
		node->height = 1 + maxInt(height(node->right), height(node->left));
		node->heightRebuild = false;
	}


	return node->height;

}

void balanceRight(Node *node)
{
	node->heightRebuild = true;

	int itemTemp = node->data;
	Node *left = node->left;
	Node *alfa = node->left->left;
	Node *beta = node->left->right;
	Node *gamma = node->right;
	//Node *node4 = node;

	node->data = left->data;
	left->data = itemTemp;

	node->right = left;
	node->left = alfa;
	node->right->left = beta;
	node->right->right = gamma;

	if (node->right != NULL)
	{
		node->right->heightRebuild = true;
		node->right->parent = node;
	}

	if (node->left != NULL)
	{
		node->left->heightRebuild = true;
		node->left->parent = node;
	}

	if (node->right->left != NULL)
	{
		node->right->left->heightRebuild = true;
		node->right->left->parent = node->right;
	}

	if (node->right->right != NULL)
	{
		node->right->right->heightRebuild = true;
		node->right->right->parent = node->right;
	}


}


void balanceLeft(Node *node)
{

	node->heightRebuild = true;

	int itemTemp = node->data;
	Node *right = node->right;
	Node *alfa = node->left;
	Node *beta = node->right->left;
	Node *gamma = node->right->right;

	node->data = right->data;
	right->data = itemTemp;

	node->left = right;
	node->right = gamma;
	node->left->left = alfa;
	node->left->right = beta;

	if (node->right != NULL)
	{
		node->right->heightRebuild = true;
		node->right->parent = node;
	}

	if (node->left != NULL)
	{
		node->left->heightRebuild = true;
		node->left->parent = node;
	}

	if (node->left->left != NULL)
	{
		node->left->left->heightRebuild = true;
		node->left->left->parent = node->left;
	}

	if (node->left->right != NULL)
	{
		node->left->right->heightRebuild = true;
		node->left->right->parent = node->left;
	}

}

void delete(Tree *tree, int item)
{

	if (tree->firstNode == NULL)
		return;

	//Na wszelki wypadek
	tree->firstNode->heightRebuild = true;

	if (tree->firstNode->data == item && height(tree->firstNode) == 1)
	{
		tree->firstNode = NULL;
		return;
	}

	Node *node = findPrivate(tree->firstNode, item, true);

	if (node == NULL)
	{
		//Nie ma takiej liczby
		return;
	}

	//node->heightRebuild = true;

	if (node->left == NULL && node->right == NULL)
	{

		Node *parent = node->parent;

		if (parent->left == node)
			parent->left = NULL;
		else
			parent->right = NULL;

		fixTree(parent);

		return;

	}

	//Je�eli dany w�ze� ma jednego syna to ten syn nie ma �adnych syn�w

	if (node->left == NULL)
	{
		node->data = node->right->data;
		node->right = NULL;
		fixTree(node);

		return;
	}

	if (node->right == NULL)
	{
		node->data = node->left->data;
		node->left = NULL;
		fixTree(node);

		return;
	}


	//Szukamy następnika
	Node *nastepnik = minPrivate(node->right, true);

	node->data = nastepnik->data;

	if (nastepnik->parent->right == nastepnik)
		nastepnik->parent->right = NULL;
	else
		nastepnik->parent->left = NULL;


}


void fixTree(Node *node)
{
	//Naprawiamy drzewo
	while (node != NULL)
	{
		int balanceNode = balance(node);

		if (balanceNode >= 2)
		{

			if (balance(node->left) == -1)
			{
				balanceLeft(node->left);
			}

			balanceRight(node);

		}
		else if (balanceNode <= -2)
		{

			if (balance(node->right) == 1)
			{
				balanceRight(node->right);
			}

			balanceLeft(node);

		}
		else
		{
			node = node->parent;
		}

	}


}


Node *findPrivate(Node *node, int item, bool refreshHeight)
{

	while (node != NULL && node->data != item)
	{
		if (refreshHeight)
			node->heightRebuild = true;

		if (item > node->data)
		{
			node = node->right;
		}
		else
		{
			node = node->left;
		}

	}

	if (node != NULL && refreshHeight)
		node->heightRebuild = true;

	return node;
}

void find(Tree *tree, int item)
{
	if (findPrivate(tree->firstNode, item, false) == NULL)
	{
		printf("%d\n", 0);
	}
	else
	{
		printf("%d\n", 1);
	}
}

void max(Tree *tree)
{

	if (tree->firstNode == NULL)
	{
		printf("\n");
		return;
	}

	printf("%d\n", maxPrivate(tree->firstNode)->data);

}

void min(Tree *tree)
{

	if (tree->firstNode == NULL)
	{
		printf("\n");
		return;
	}

	printf("%d\n", minPrivate(tree->firstNode, false)->data);

}

Node *maxPrivate(Node *node)
{

	while (node->right != NULL)
	{
		node = node->right;
	}

	return node;

}

Node *minPrivate(Node *node, bool refreshHeight)
{

	while (node->left != NULL)
	{
		if (refreshHeight)
			node->heightRebuild = true;

		node = node->left;
	}

	if (node != NULL && refreshHeight)
		node->heightRebuild = true;

	return node;

}

void printTree(Tree *tree)
{
	print_t(tree->firstNode);
}

//http://stackoverflow.com/a/13755911

int _print_t(Node *tree, int is_left, int offset, int depth, char **s, int numberWidth, char* numberFormat)
{
	char b[20];
	int width = numberWidth + 2;

	if (!tree) return 0;

	sprintf(b, numberFormat, tree->data);

	int left = _print_t(tree->left, 1, offset, depth + 1, s, numberWidth, numberFormat);
	int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s, numberWidth, numberFormat);

#ifdef COMPACT
    for (int i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[depth - 1][offset + left + width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[depth - 1][offset - width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';
    }
#else
	for (int i = 0; i < width; i++)
		s[2 * depth][offset + left + i] = b[i];

	if (depth && is_left)
	{

		for (int i = 0; i < width + right; i++)
			s[2 * depth - 1][offset + left + width / 2 + i] = '-';

		s[2 * depth - 1][offset + left + width / 2] = '+';
		s[2 * depth - 1][offset + left + width + right + width / 2] = '+';

	}
	else if (depth && !is_left)
	{

		for (int i = 0; i < left + width; i++)
			s[2 * depth - 1][offset - width / 2 + i] = '-';

		s[2 * depth - 1][offset + left + width / 2] = '+';
		s[2 * depth - 1][offset - width / 2 - 1] = '+';
	}
#endif

	return left + width + right;
}

void print_t(Node *tree)
{
	//char s[20][255];

	//W RAZIE PROBLEMÓW ZMIENIAć TYLKO TO:
	int width = 5;
	char *numberFormat = "(%05d)";



	//Liczymy rozmiar drzewa (paradoksalnie tutaj x to wysokosc, a y to szerokosc)
	int x = height(tree) * 2;
	int y = (int) pow(2, height(tree)) - 1;
	y *= y + 2;

	char **s = twoDimentialArray(x, y);

	//for (int i = 0; i < x; i++)
	//	sprintf(s[i], "%500s", " ");

	_print_t(tree, 0, 0, 0, s, width, numberFormat);

	for (int i = 0; i < x; i++)
		printf("%s\n", s[i]);
}

char **twoDimentialArray(int x, int y)
{

	char **array = malloc(sizeof(char *) * x);

	for (int i = 0; i < x; i++)
	{
		array[i] = malloc(sizeof(char) * y + 1);

		for (int j = 0; j < y; j++)
		{
			array[i][j] = ' ';
		}

		array[i][y] = '\0';

	}

	return array;

}