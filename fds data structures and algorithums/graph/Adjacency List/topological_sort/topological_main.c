#include <stdio.h>
#include "../adj_list.h"
extern int TopologicalSort(Graph* graph, int* result);

int main(){
    int V = 6;
    Graph* g = CreateGraph(V);
    if(!g) return 1;
    AddEdge(g, 5, 2, 0);
    AddEdge(g, 5, 0, 0);
    AddEdge(g, 4, 0, 0);
    AddEdge(g, 4, 1, 0);
    AddEdge(g, 2, 3, 0);
    AddEdge(g, 3, 1, 0);

    int* res = (int*)malloc(V * sizeof(int));
    if(TopologicalSort(g, res)){
        printf("Topological order:\n");
        for(int i=0;i<V;i++) printf("%d ", res[i]);
        printf("\n");
    } else {
        printf("Graph has a cycle.\n");
    }
    DestroyGraph(g);
    free(res);
    return 0;
}
