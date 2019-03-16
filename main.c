#include "list.h"
#include "stack.h"
#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define MIN(a,b) ((a) < (b) ? a:b)
#define MAX(a,b) ((a) > (b) ? a:b)

typedef list_t List;

void getInput(int* n, List** list);
void dfs_visit(int u, List list, int subtree, int* subtree_ids, int* low,
	int* n_lows, Stack scc, int* on_stack, int* is_art);


int main(){
	int n, i;
	List* list;					/* list[i] adjacency list of vertex i */


	getInput(&n, &list);

	int visited[n];
	int subtree = 1;			/* current subtree */
	int subtree_ids[n];		/* subtree_ids[i] has the vertex of the i'th subtree */
	int low[n];						/* vertices with the same low are in the same SCC */
	int n_lows[n];				/* n_lows[i] has number of vertices with the low i */
	Stack scc;
	int on_stack[n];
	int is_art[n];				/* is articulation point */

	for(i = 0; i < n; i++){
		visited[i] = FALSE;
		subtree_ids[i] = 0;
		low[i] = 0;
		n_lows[i] = 0;
		on_stack[i] = FALSE;
		is_art[i] = FALSE;
	}

	initStack(scc);

	/* iterate over non-visited vertices */
	for(i = 0; i < n; i++){
		if(!visited[i]){
			subtree++;
			dfs_visit(i, list[i], subtree, subtree_ids, low,
				n_lows, scc, on_stack, is_art);
		}
	}

	return 0;
	/* FIXME use gathered data */
}


void dfs_visit(int u, List list, int subtree, int* subtree_ids, int* low,
	int* n_lows, Stack scc, int* on_stack, int* is_art){

	int v, w, i;
	subtree_ids[subtree] = MAX(u, subtree_ids[subtree]);
	visited[u] = TRUE;
	low[u] = u;
	pushStack(u, scc);
	on_stack[u] = TRUE;

	/* for each adjacent vertex of u */
	for(i = 0, v = getList(list, i); v != NULL; v = getList(list, ++i)){
		if(!visited[v]){
			dfs_visit(v, list, subtree, subtree_ids, low,
				n_lows, scc, on_stack, is_art);
		}

		if(on_stack[v]){
			low[u] = MIN(low[v], low[u]);
		}
	}

	if(u == low[u]){						/* if u is root of a SCC */
		while(TRUE){
			w = popStack(scc);
			on_stack[w] = FALSE;
			low[w] = low[u];				/* set the lows of found SCC */
			n_lows[low[u]] += 1;		/* increment number of vertices with that low */

			if(w == u){							/* if it's the root of the SCC */
				if(getLength(list) > 1){ /* and has more then 1 edge */
					is_art[u] = TRUE;		/* then it's an articulation point */
				}
				break;
			}
		}
	}
}
