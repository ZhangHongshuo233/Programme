#include <stdio.h>
#include <limits.h>
#define MAX_V 100
extern int FordFulkerson_Naive(int V, int graph[MAX_V][MAX_V], int s, int t);

int main(){
    int V = 4;
    int graph[MAX_V][MAX_V] = {0};
    graph[0][1] = 100;
    graph[0][2] = 100;
    graph[1][2] = 1;
    graph[1][3] = 100;
    graph[2][3] = 100;

    int maxflow = FordFulkerson_Naive(V, graph, 0, 3);
    printf("Ford-Fulkerson naive max flow = %d\n", maxflow);
    return 0;
}
