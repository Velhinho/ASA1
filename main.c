#include <stdin.h>

#define TRUE 1
#define FALSE 0


void getInput(int* n, list* list);
void dfs_visit(int i, List list, int subtree, int* subtree_ids, int low,
	int* n_lows, Stack scc, int* on_stack, int* is_art);


int main(){
	int n;
	List list;

	getInput(&n, &list);

	int visited[n];
	int subtree = 1;			/* current subtree */
	int subtree_ids[n];		/* subtree_ids[i] has the vertex of the i'th subtree */
	int low[n];						/* vertices with the same low are in the same SCC */
	int n_lows[n];				/* n_lows[i] has number of vertices with the low i */
	Stack scc;
	int on_stack[n];
	int is_art[n];				/* is articulation point */

	for(int i = 0; i < n; i++){
		visited[i] = FALSE;
		subtree_ids[i] = 0;
		low[i] = 0;
		n_lows = 0;
		on_stack = FALSE;
		is_art = FALSE;
	}

	initStack(scc);

	/* Iterate over non-visted vertices */
	for(i = 0; i < n; i++){
		if(!visted[i]){
			subtree++; dfs_visit(i, list, subtree, subtree_ids, low,
				n_lows, scc, on_stack, is_art);
		}
	}

	/* FIXME use gathered data */
}
