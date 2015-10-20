#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "graph.h"

#define Object Vertex

typedef struct stack Stack;

typedef struct stack
{
	Object **objects;
	int lastObjectID;
} STACK;

Object *stackPop(Stack *object);
void stackPush(Object *object, Stack *stack);
#endif
