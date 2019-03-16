#ifndef LIST
#define LIST


typedef struct nodesList
{
	int verticeId;
	struct nodesList* nextNode;
}nodesList_t;

typedef nodesList_t* list_iter_t;

typedef struct list{
	nodesList_t head;
	int size;
}list_t;

void list_iter_reset( list_iter_t* pIter, list_t* pList);
nodesList_t* list_insert (nodesList_t* pList, int v);
int get_lenght (list_t* pList);


#endif