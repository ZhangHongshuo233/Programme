#include <stdio.h>
#define MAX_V 100
extern int MaxCapacityPath(int V, int graph[MAX_V][MAX_V], int s, int t);

int main(){
    int V = 4;
    int graph[MAX_V][MAX_V] = {0};
    graph[0][1] = 5;
    graph[0][2] = 3;
    graph[1][3] = 4;
    graph[2][3] = 2;

    int cap = MaxCapacityPath(V, graph, 0, 3);
    printf("Max capacity path = %d\n", cap);
    return 0;
}
