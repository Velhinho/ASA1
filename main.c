#include <stdin.h>

#define TRUE 1
#define FALSE 0


int main(){
	int n;
	list list;

	getInput(&n, &list);

	int visited[n];
	int subtree = 1;			/* current subtree */
	int subtree_ids[n];		/* subtree_ids[i] has the vertex of the i'th subtree */
	int low[n];
	int n_lows[n];
}
