#ifndef STACK
#define STACK


struct stack
{
	int size;  //it does matter;
	int head;
	int *stackMembers;
};

int full(struct stack *s);
int empty(struct stack *s);
void push(int v, struct stack *s);
int pop(struct stack *s);
void emptyStack(struct stack *s);
void freeStack(struct stack *s);

#endif