#ifndef STACK
#define STACK

#include "list.h"

typedef list_t stack_t;

stack_t* initStack();
void freeStack(stack_t* stack);
void pushStack(stack_t* stack, int vertex);
int popStack(stack_t* stack);

#endif
