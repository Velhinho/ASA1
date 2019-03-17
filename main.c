#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define INFINITY -1
#define TIME 0
#define D    1
#define LOW  2
#define PI   3
#define AP_COUNT 0
#define MAX_AP   1
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) < (b) ? (b) : (a))

typedef int  graph_vertex_t;

typedef struct _graph_node graph_node_t;

typedef struct _graph      graph_t;

struct _graph_node {
  graph_vertex_t vertex;
  graph_node_t *next;
};

struct _graph {
  int V, E, nC;
  graph_node_t **adjlist;
};


//HARDCODED. HAVE TO WORK ON THIS, OR MAYBE NOT!
int worseThanSex[10];


graph_t *graph_new(int V) {
  graph_t *graph = NULL;
  
  if(V > 0 && (graph = (graph_t*)malloc(sizeof(struct _graph))) != NULL) {
    graph->V = V;
    graph->E = 0;
    graph->nC = 0;
    graph->adjlist = (graph_node_t**)malloc(V * sizeof(struct _graph_node*));
  }
  
  return graph;
}

void graph_free(graph_t *graph) {
  int i; 
  for(i = 0; i < graph->V; ++i) {
    graph_node_t *head = graph->adjlist[i];
    while(head != NULL) {
      graph_node_t *temp = head;
      head = head->next;
      free(temp);
    }
  }
  free(graph->adjlist);
  free(graph);
}

void graph_add_edge(graph_t *graph, graph_vertex_t u, graph_vertex_t v) {
  if((u > 0 && u <= graph->V) && (v > 0 && v <= graph->V)) {
    graph_node_t *w = (graph_node_t*)malloc(sizeof(struct _graph_node));
    graph_node_t *x = (graph_node_t*)malloc(sizeof(struct _graph_node));

    if(w != NULL && x != NULL) {
      w->vertex = u;
      x->vertex = v;
      w->next = graph->adjlist[v - 1];
      x->next = graph->adjlist[u - 1];
      
      graph->adjlist[v - 1] = w;
      graph->adjlist[u - 1] = x;
    }
    else {
      exit(EXIT_FAILURE);
    }
    
    graph->E++;
  }
}


void DFS_Tarjan(graph_t *graph, graph_vertex_t u, int **lista, int ap_data[2]) {
  graph_node_t *node = graph->adjlist[u - 1];
  graph_vertex_t adj;
  bool isArticulationPoint = false;
  int childCount = 0;
  
  lista[D][u - 1] = lista[TIME][0];
  lista[LOW][u - 1] = lista[TIME][0];
  ++lista[TIME][0];
  worseThanSex[graph->nC] = MAX(worseThanSex[graph->nC],u);

  while(node != NULL) {
    adj = node->vertex;
    printf("%d\t%d\n", worseThanSex[graph->nC],u);

    if(lista[D][adj - 1] == INFINITY) {
      lista[PI][adj - 1] = u;
      ++childCount;
      DFS_Tarjan(graph, adj, lista, ap_data);

      if(lista[D][u - 1] <= lista[LOW][adj - 1]) {
        isArticulationPoint = true;
      }
      else {
        lista[LOW][u - 1] = MIN(lista[LOW][u - 1], lista[LOW][adj - 1]);
      }
    }

    else if(adj != lista[PI][u - 1]) {
      lista[LOW][u - 1] = MIN(lista[LOW][u - 1], lista[D][adj - 1]);
    }
    node = node->next;
  }

  //check if cut vertex!
  if((lista[PI][u - 1] == INFINITY && childCount > 1) || (lista[PI][u - 1] != INFINITY && isArticulationPoint)) {
    ++ap_data[AP_COUNT]; 
    if(ap_data[MAX_AP] == INFINITY){
      ap_data[MAX_AP] = u;
    }
    else {
      ap_data[MAX_AP] = MAX(ap_data[MAX_AP], u);
    }
  }
}


void CV_Tarjan(graph_t *graph, int ap_data[2]) {
  int **lista, i;

  ap_data[AP_COUNT] = 0;
  ap_data[MAX_AP] = INFINITY;

  lista = (int**)malloc(4 * sizeof(int*));
  if(lista != NULL) {
    lista[TIME] = (int*)malloc(sizeof(int));
    lista[D] = (int*)malloc(graph->V * sizeof(int));
    lista[LOW] = (int*)malloc(graph->V * sizeof(int));
    lista[PI] = (int*)malloc(graph->V * sizeof(int));
  }

  lista[TIME][0] = 0;
  for(i = 0; i < graph->V; i++) {
    lista[D][i] = INFINITY;
    lista[PI][i] = INFINITY;
  }

  for(i=0; i<graph->V;i++){
    if(lista[D][i++] == INFINITY){
      graph->nC++;
      worseThanSex[graph->nC] = 1;
      DFS_Tarjan(graph, i, lista, ap_data);
    }
  }

  free(lista[TIME]);
  free(lista[D]);
  free(lista[LOW]);
  free(lista[PI]);
  free(lista);
}

int main() {
  int V, E, i, origem, destino;
  int ap_data[3];
  graph_t *graph;
  
  scanf("%d", &V);
  scanf("%d", &E);
  graph = graph_new(V);

  int list[V];

  for(i=0;i<E;i++){
    scanf("%d %d", &origem, &destino);
    graph_add_edge(graph, origem, destino);
  }

  CV_Tarjan(graph, ap_data);

  printf("%d\n", graph->nC);
  for(i=1;i <= graph->nC; i++){
    printf("%d ", worseThanSex[i]);
  }
  printf("\n");
  printf("%d\n", ap_data[0]);
  graph_free(graph);

  return 0;
}
