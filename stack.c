#include "stack.h"
#include <stdlib.h>

typedef list_t stack_t;


void initStack(stack_t* stackPtr){

	stackPtr = (stack_t*)malloc(sizeof(stack_t));

	stackPtr->size = 0;
	stackPtr->start = NULL;
	stackPtr->end = NULL;
}


void freeStack(stack_t* stack){
	node_t* node = stack->start;
	node_t* next = stack->start->next;

	while(next){
		free(node);
		node = next;
		next = next->next;
	}
	free(node);
	free(stack);
}


void pushStack(stack_t* stack, int vertex){

	node_t* node = (node_t*)malloc(sizeof(node_t));
	node->vertex = vertex;
	node->next = NULL;

	/* If the stack is empty */
	if(!(stack->start)){
		stack->start = node;
	}

	node->next = stack->start;
	stack->start = node;
}


int popStack(stack_t* stack){
/* Returns -1 if empty */
	int ret;
	node_t* node = stack->start;

	if(!node) return -1;

	ret = node->vertex;
	free(node);
	return ret;
}
