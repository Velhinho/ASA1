#include "list.h"
#include <stdlib.h>


void initList(list_t* listPtr){

	listPtr = (list_t*)malloc(sizeof(list_t));

	listPtr->size = 0;
	listPtr->start = NULL;
	listPtr->end = NULL;
}


void freeList(list_t* list){
	node_t* node = list->start;
	node_t* next = list->start->next;

	while(next){
		free(node);
		node = next;
		next = next->next;
	}
	free(node);
	free(list);
}


int getSizeList(list_t* list){
	return list->size;
}


void addList(list_t* list, int vertex){

	node_t* node = (node_t*)malloc(sizeof(node_t));
	node->vertex = vertex;
	node->next = NULL;
	list->size++;

	/* If the list is empty */
	if(!(list->start)){
		list->start = node;
		list->end = node;
	}

	else{
		list->end->next = node; /* Old last element points to the new last element */
		list->end = node;	/* Sets the new last element as last in the list */
 }
}


int getList(list_t* list, int n){
/* Returns -1 if list too small or empty */

	node_t* node = list->start;
	int i = 0;

	if(n < 0 || n > list->size)
		return -1;

	while(i < n){
		node = node->next; i++;
	}

	return node->vertex;
}

int removeList(list_t* list, int n){
	/* Return 1 if success, 0 otherwise */

	node_t* previous = list->start;
	node_t* node = list->start->next;
	int i = 1;

	if(n < 0 || n > list->size)
		return 0;

	if(n == 0){
		list->start = node; free(previous);
	}

	while(i < n){
		previous = node; node = node->next;
		i++;
	}
	previous->next = node->next;
	free(node);

	return 1;
}
