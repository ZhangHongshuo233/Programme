#include <stdio.h>
#include <stdlib.h>
#include "../edge_list.h"

int main() {
    /* 简单示例：构建一个带权无向图并计算 MST */
    int V = 4;
    int E = 5;
    EdgeGraph* graph = CreateEdgeGraph(V, E);
    if (!graph) return 1;

    AddEdgeToGraph(graph, 0, 1, 10);
    AddEdgeToGraph(graph, 0, 2, 6);
    AddEdgeToGraph(graph, 0, 3, 5);
    AddEdgeToGraph(graph, 1, 3, 15);
    AddEdgeToGraph(graph, 2, 3, 4);

    int total = KruskalMST(graph);
    printf("Kruskal MST total weight = %d\n", total);

    DestroyEdgeGraph(graph);
    return 0;
}
