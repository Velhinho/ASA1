#include <stdlib.h>
#include "list.h"

void list_iter_reset(list_iter_t* pIter, list_t* pList){
	*pIter = &(pList->head);
}

nodesList_t* list_insert(nodesList_t* pList, int v){
	nodesList_t* newNode = malloc(sizeof(list_t));
	newNode->verticeId = v;
	newNode->nextNode = pList;
	return newNode;
}
int get_lenght(list_t* pList){

	return pList->size;

}