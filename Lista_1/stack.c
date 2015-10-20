#include "graph.h"
#include "stack.h"

#define Object Vertex

Object *stackPop(Stack *stack)
{
	stack->lastObjectID--;
	return stack->objects[stack->lastObjectID];
}


void stackPush(Object *object, Stack *stack)
{
	stack->objects[stack->lastObjectID] = object;
	stack->lastObjectID++;
}
