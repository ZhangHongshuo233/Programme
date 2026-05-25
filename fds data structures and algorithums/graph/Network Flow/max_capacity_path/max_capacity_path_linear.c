/*
 * 寻找最大容量路径的算法实现
    * 适用于网络流算法中的增广路径寻找
    * 通过改进的 Dijkstra 算法实现，单次查找的时间复杂度为 O(V^2)
    * 总时间复杂度取决于增广路径的数量，最坏情况下为 O(V^2 * E)
    * 输入：图的顶点数 V，残量网络 residual，起点 s，终点 t，父节点数组 parent
    * 输出：返回是否找到增广路径，并通过 parent 数组记录路径信息
    * 注意：residual[u][v] 表示从 u 到 v 的剩余容量，初始时等于原图的容量
 */
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_V 100
#define INF (INT_MAX>>1)

/* 改进的 Dijkstra 算法：寻找从 S 到 T 瓶颈容量最大的路径 */
bool dijkstra_max_cap(int V, int residual[MAX_V][MAX_V], int s,int t, int parent[]) {
    int max_cap[MAX_V]; /* 记录从 s 到 i 的路径上，能通行的最大瓶颈容量 */
    bool visited[MAX_V];

    for(int i = 0; i < V; i++) max_cap[i] = 0;
    max_cap[s] = INF;
    parent[s] = -1;
    
    for(int cnt = 0; cnt < V; cnt++) {
        /* 挑出一个目前 max_cap 最大且未访问的顶点 */
        int u = -1, best_cap = -1;
        for(int i = 0; i < V; i++) {
            if(!visited[i] && max_cap[i] > best_cap) {
                best_cap = max_cap[i];
                u = i;
            }
        }

        /* 如果找不到路，或者已经摸到了终点，或者最大水管没水了，提前结束 */
        if(u == -1 || u == t || best_cap == 0) break;

        visited[u] = true;

        /* 2. 松弛操作：更新邻居 */
        for(int v = 0; v < V; v++) {
            if(!visited[v] && residual[u][v] > 0) {
                /* 更新从 s 到 v 的最大瓶颈容量 */
                int new_cap = (max_cap[u] < residual[u][v]) ? max_cap[u] : residual[u][v];
                /* 贪心：如果找到了更大的瓶颈容量，更新记录 */
                if(new_cap > max_cap[v]) {
                    max_cap[v] = new_cap;
                    parent[v] = u;
                }
            }
        }
    }
    return max_cap[t] > 0;  
}

int MaxCapacityPath(int V, int graph[MAX_V][MAX_V], int s, int t){
    int residual[MAX_V][MAX_V];
    for(int i = 0; i < V; i++) {
        for(int j = 0; j < V; j++) {
            residual[i][j] = graph[i][j]; /* 初始化残量网络 */
        }
    }

    int parent[MAX_V];  
    int max_flow = 0;

    /* 主循环：不断寻找增广路径并更新最大流 */
    while(dijkstra_max_cap(V, residual, s, t, parent)) {
        int path_flow = INF;

        /* 计算增广路径上的最小残量 */
        for(int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            if(residual[u][v] < path_flow) {
                path_flow = residual[u][v];
            }
        }

        /* 更新残量网络 */
        for(int v = t; v != s; v = parent[v]){
            int u = parent[v];
            residual[u][v] -= path_flow;
            residual[v][u] += path_flow; 
        }

        max_flow += path_flow;
    }
    return max_flow;
}