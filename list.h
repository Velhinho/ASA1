#ifndef LIST
#define LIST

typedef struct Node {
	int vertex;
	struct Node* next;
} node_t;

typedef struct List{
	int size;
	node_t* start;
	node_t* end;
} list_t;

list_t* initList();
void freeList(list_t* list);
int getSizeList(list_t* list);
void addList(list_t* list, int vertex);
int getList(list_t* list, int n);
int removeList(list_t* list, int n);

#endif
