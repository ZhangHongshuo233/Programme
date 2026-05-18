#include <stdio.h>
#include <stdlib.h>
#include "topological_sort.c"
#include "../adj_list.c"

int main() {
    int V = 6;
    Graph* graph = CreateGraph(V);
    AddDirectedEdge(graph, 5, 2, 0);
    AddDirectedEdge(graph, 5, 0, 0);
    AddDirectedEdge(graph, 4, 0, 0);
    AddDirectedEdge(graph, 4, 1, 0);
    AddDirectedEdge(graph, 2, 3, 0);
    AddDirectedEdge(graph, 3, 1, 0);

    printf("Graph adjacency list:\n");
    PrintGraph(graph);

    int* result = (int*)malloc(V * sizeof(int));
    if (TopologicalSort(graph, result)) {
        printf("Topological Sort Order:\n");
        for (int i = 0; i < V; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");

        if (IsTopSort(graph, result)) {
            printf("Validation successful: The sequence is a valid topological sort.\n");
        } else {
            printf("Validation failed: The sequence is NOT a valid topological sort.\n");
        }
    } else {
        printf("The graph has a cycle. Topological sort not possible.\n");
    }

    free(result);
    DestroyGraph(graph);
    return 0;
}
