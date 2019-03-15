#include <stdio.h>
#include <stdlib.h>
#define MIN(a,b) ((a) < (b) ? a:b)
typedef struct linkedList *link;
typedef struct node Node;

/*typedef struct stack{
	int top
	int *vertices;
} Stack;*/

struct linkedList{
	struct node *v;
	struct linkedList *next;
};

struct edge{
	int origem;
	int destino;
};

struct node{
	int vertex;
	int low;
	int disc;
	int isInStack;
	int visited;
	int isCut;
	int* idMax;
	struct linkedList *adj;
};

typedef struct graph{
	struct node* vertices;
	int nV;
	int nE;
	int nComponents;
	int sccs;
	int visited;
	link stack;
}graph;

link addToList(link head, struct node *V){
	link newNode= malloc(sizeof(link));
	newNode->v = V;
	newNode->next = head;
	return newNode;
}

void push(link *top, struct node* v){
	*top = addToList(*top, v);
	v->isInStack=1;
}

struct node* pop(link *h){
	link tmp = *h;
	struct node* vertex = tmp->v;
	vertex->isInStack = -1;
	*h = (*h)->next;
	return vertex;
}

Node createVertice(int vertex){
	Node new;
	new.vertex = vertex;
	new.isInStack=0;
	new.disc=-1;
	new.low=-1;
	new.isCut = -1;
	new.adj = NULL;
	new.idMax=NULL;
	return new;
}


graph* initGraph(int size){
	int i;
	graph* newGraph = malloc(sizeof(struct graph));
	newGraph->visited=1;
	newGraph->vertices = (struct node*) malloc (sizeof(struct node) * size);
	newGraph->nV = size;
	newGraph->nE = 0;
	newGraph->sccs = 0;
	newGraph->nComponents=0;
	newGraph->stack =NULL;
	for(i=0;i<size;i++){
		newGraph->vertices[i] = createVertice(i);
	}
	return newGraph;
}
void tarjanVisit(graph *g, int vertex){
	struct node* v = &g->vertices[vertex];
	v->low = g->visited;
	v->disc = g->visited;
	g->visited++;
	push(&g->stack, v);
	link aux;

	for(aux = v->adj; aux!=NULL; aux=aux->next){
		Node* u = aux->v;
		if(u->disc == -1 || u->isInStack == 1){
			if(u->disc == -1){
				tarjanVisit(g, u->vertex);
			}
			v->low=MIN(v->low, u->low);
		}
	}
	if(v->disc == v->low){
		g->sccs ++;
		Node* w = NULL;
		int* indiceMaior = malloc(sizeof(int));
		*indiceMaior = 0;
		do{
			w= pop(&g->stack);
			w->idMax = indiceMaior;
			if(*indiceMaior == g->nV || w->vertex > *indiceMaior)
				*indiceMaior = w->vertex;
		}while(w->vertex != v->vertex);
	}
}

void DFS_Components(graph *g){
	int i, components=0;

	for(i=0; i< g->nV;i++){
		if(g->vertices[i].disc == -1){
			g->nComponents++;
			tarjanVisit(g,i);
		}
	}
}

int main(){

	int V, E, origem, destino, i;

	scanf("%d", &V);
	scanf("%d", &E);

	graph* g= initGraph(V);

	for(i=0;i<E; i++){
		scanf("%d %d", &origem, &destino);
		g->nE++;
		g->vertices[origem-1].adj = addToList(g->vertices[origem-1].adj, &g->vertices[destino-1]);
	}
	
	DFS_Components(g);
	printf("%d\n%d\n", g->nComponents, g->sccs);

	return 0;
}