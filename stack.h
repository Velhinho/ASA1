#ifndef STACK
#define STACK

#include "list.h"

void initStack(list_t* stack);
void freeStack(list_t* stack);
void pushStack(list_t* stack, int vertex);
int popStack(list_t* stack);

#endif
