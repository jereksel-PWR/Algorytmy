#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED

#include "stdbool.h"

typedef struct tree Tree;
typedef struct node Node;

typedef struct node
{
	Node *left;
	Node *right;
	Node *parent;
	int data;
	int height;
	bool heightRebuild;
} NODE;


typedef struct tree
{
	Node *firstNode;
} TREE;


void insert(Tree *tree, int item);
Tree *create_tree();
void inorder(Tree *tree);
void delete(Tree *tree, int item);
void find(Tree *tree, int item);
void max(Tree *tree);
void min(Tree *tree);
void printTree(Tree *tree);

#endif
