#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

struct stack* stack_alloc (int stackSize){

	struct stack *pStack = (struct stack *)malloc(sizeof(struct stack));
	pStack->size = stackSize;
	pStack->head = -1;
	pStack->stackMembers = (int *)malloc(sizeof(struct stack)*stackSize);
	return pStack;
}

int full(struct stack *s){
	return s->head == s->size - 1;
}


int empty(struct stack *s){
	return s->head == -1;
}

void push(int v, struct stack *s){
	if (!full(s))
		s->stackMembers[++(s->head)] = v;
}

int pop(struct stack *s){
	if (!empty(s))
		return s->stackMembers[s->head--];
}

int getSize(struct stack* s){
	return (s->size);
}

void emptyStack(struct stack *s){
	while (!empty(s))
		pop(s);
}

void freeStack(struct stack *s){
	free(s->stackMembers);
	free(s);
}