/*
 * Edmonds-Karp 算法实现
    * 复杂度分析：
        - 时间复杂度为 O(V * E^2)，其中 V 是顶点数，E 是边数。因为每次寻找增广路径使用 BFS，时间复杂度为 O(E)，而最多需要 O(V * E) 次增广路径。
    * 适用场景：
        - 适用于中小规模的网络流问题，尤其是当边的容量较小且增广路径较多时。
        - 不适合大规模网络流问题，因为时间复杂度较高。
    * 优化建议：
        - 使用 Dinic 算法或 Push-Relabel 算法等更高级的网络流算法，可以进一步提高效率，尤其是在大规模网络流问题中。
 */

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_V 100
#define INF (INT_MAX>>1)

/* 使用 BFS 寻找最短的增广路径 */
bool bfs(int V, int residual[MAX_V][MAX_V], 
         int s, int t, int parent[]){
    bool visited[MAX_V] = {false};
    int queue[MAX_V], front = 0, rear = 0;

    queue[rear++] = s;  /* 将起点加入队列 */
    visited[s] = true;
    parent[s] = -1;     /* 起点没有父节点 */

    while(front < rear){
        int u = queue[front++];

        for(int v = 0; v < V; v++){
            if(!visited[v] && residual[u][v] > 0){
                parent[v] = u;
                visited[v] = true;
                if(v == t) return true;
                queue[rear++] = v;
            }
        }
    }
    return false;
}

/* Edmonds-Karp 算法 */
int EdmondsKarp(int V, int graph[MAX_V][MAX_V], int s, int t){
    int residual[MAX_V][MAX_V];
    for(int i = 0; i < V; i++)
        for(int j = 0; j < V; j++)
            residual[i][j] = graph[i][j];

    int parent[MAX_V];
    int max_flow = 0;

    while(bfs(V, residual, s, t, parent)){
        int path_flow = INF;
        /* 回溯路径，找到瓶颈容量 */
        for(int v = t; v != s; v = parent[v]){
            int u = parent[v];
            if(residual[u][v] < path_flow)
                path_flow = residual[u][v];
        }

        /* 沿着路径更新残量图 */
        for(int v = t; v != s; v = parent[v]){
            int u = parent[v];
            residual[u][v] -= path_flow;
            residual[v][u] += path_flow;
        }
        max_flow += path_flow;
    }
    return max_flow;
}