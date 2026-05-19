/*
 * 朴素 Ford-Fulkerson 算法实现
    * 复杂度分析：
        - 最坏情况下，时间复杂度为 O(E * f)，其中 E 是边数，f 是最大流量。因为每次找到增广路径后，可能只增加 1 单位的流量。
        - 由于可能存在大量的增广路径，尤其是在容量较小的边较多的情况下，算法效率可能非常低。
    * 适用场景：    
        - 适用于小规模网络流问题，或者当边的容量较大时，增广路径较少的情况。
        - 不适合大规模网络流问题，因为可能需要大量的增广路径才能达到最大流。
        * 优化建议：
        - 使用 BFS 替代 DFS 来寻找增广路径（即 Edmonds-Karp 算法），可以保证每次找到的增广路径都是最短的，从而将时间复杂度降低到 O(V * E^2)。
        - 使用 Dinic 算法或 Push-Relabel 算法等更高级的网络流算法，可以进一步提高效率，尤其是在大规模网络流问题中。
 */


#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_V 100
#define INF (INT_MAX>>1)

/* 内部 DFS 函数：在残量图中寻找一条增广路径 */
int dfs(int u, int t, int flow, bool visited[], 
        int residual[MAX_V][MAX_V], int V){
    if(u == t) return flow; /* 到达终点，返回这条路径的瓶颈流量 */

    visited[u] = true; /* 标记当前节点已访问 */

    for(int v = 0; v < V; v++){
        /* 如果 v 没有被访问过，并且 u 到 v 的残量大于 0 */
        if(!visited[v] && residual[u][v] > 0){
            /* 递归寻找从 v 到 t 的增广路径，流量为当前路径的瓶颈流量和 u 到 v 的残量的最小值 */
            int min_cap = (flow < residual[u][v]) ? 
                            flow : residual[u][v];
            int pushed = dfs(v, t, min_cap, visited, residual, V);

            if(pushed > 0){
                /* 找到路径了！处理反悔机制 (残量图核心) */
                residual[u][v] -= pushed;  /* 正向边减去流量 */
                residual[v][u] += pushed;  /* 反向边增加流量 */
                return pushed;             /* 返回这条路径的流量 */
            }
        }
    }
    return 0; /* 没有找到增广路径 */
}

/* 朴素 Ford-Fulkerson 算法 */
int FordFulkerson_Naive(int V, int graph[MAX_V][MAX_V], int s, int t){
    int residual[MAX_V][MAX_V];\
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            residual[i][j] = graph[i][j];

    int max_flow = 0;
    int pushed_flow;
    bool visited[MAX_V];

    do{
        for(int i = 0; i < V; i++) 
            visited[i] = false;
        
        /* 每次尝试推入无穷大的流，DFS 会返回实际能推入的最小瓶颈 */
        pushed_flow = dfs(s, t, INF, visited, residual, V);
        max_flow += pushed_flow;
    }while(pushed_flow > 0); /* 直到找不到任何增广路径为止 */

    return max_flow;
}