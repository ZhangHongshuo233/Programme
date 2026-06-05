#include <stdio.h>
#include <stdlib.h>
#include "../adj_list.h"
#include "shortest_path.h"

int main() {
    int V = 5;
    Graph* g = CreateGraph(V);
    if (!g) return 1;

    AddEdge(g, 0, 1, 9);
    AddEdge(g, 0, 2, 6);
    AddEdge(g, 0, 3, 5);
    AddEdge(g, 0, 4, 3);
    AddEdge(g, 2, 1, 2);
    AddEdge(g, 2, 3, 4);

    DijkstraBasic(g, 0);

    DestroyGraph(g);
    return 0;
}
