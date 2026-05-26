#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "C:\Users\Lenovo\Desktop\programme\fds data structures and algorithums\heap\binary heap\min_heap\min_heap.h"
#define MAX_V 1000
#define INF 1000000000

/* ==========================================
 * 内部辅助函数：在堆内存中动态创建和销毁二维矩阵
 * ========================================== */
int** CreateMatrix(int V) {
    int** mat = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        mat[i] = (int*)calloc(V, sizeof(int)); /* calloc 自动初始化为 0 */
    }
    return mat;
}

void FreeMatrix(int** mat, int V) {
    if (!mat) return;
    for (int i = 0; i < V; i++) {
        free(mat[i]);
    }
    free(mat);
}

/* ==========================================
 * 单次寻路：基于最小堆的魔改 Dijkstra
 * ========================================== */
bool dijkstra_max_cap_heap(int V, int** residual, int s, int t, int* parent) {
    int* max_cap = (int*)malloc(V * sizeof(int));
    
    for (int i = 0; i < V; i++) {
        max_cap[i] = 0;
        parent[i] = -1;
    }
    max_cap[s] = INF;

    /* 初始化最小堆，最坏情况下可能压入 E 条边，这里用 V*V 兜底 */
    /* 由于堆是用 malloc 创建的，开 1000*1000 也是绝对安全的 */
    MinHeap* H = CreateMinHeap(V * V);
    Push(H, s, -INF);

    while (!IsEmpty(H)) {
        HeapNode current = Pop(H);
        int u = current.vertex;
        int current_real_cap = -current.dist;

        /* 懒惰删除：过滤旧数据 */
        if (current_real_cap < max_cap[u]) continue;

        if (u == t) break; 

        for (int v = 0; v < V; v++) {
            if (residual[u][v] > 0) {
                int new_cap = (max_cap[u] < residual[u][v]) ? max_cap[u] : residual[u][v];
                
                if (new_cap > max_cap[v]) {
                    max_cap[v] = new_cap;
                    parent[v] = u;
                    Push(H, v, -new_cap);
                }
            }
        }
    }
    
    bool found = max_cap[t] > 0;
    
    /* 释放局部动态内存 */
    DestroyMinHeap(H); 
    free(max_cap);
    return found;
}

/* ==========================================
 * 核心：最大容量路径网络流主函数
 * ========================================== */
int MaxCapacityFlow_Heap(int V, int** graph, int s, int t) {
    /* 动态创建残量图，避开栈溢出 */
    int** residual = CreateMatrix(V);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            residual[i][j] = graph[i][j];
        }
    }

    int* parent = (int*)malloc(V * sizeof(int));
    int max_flow = 0;

    printf("=== 极客版：调用自有 MinHeap API 实现的最大容量增广路 ===\n");
    
    while (dijkstra_max_cap_heap(V, residual, s, t, parent)) {
        int path_flow = INF;
        
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            if (residual[u][v] < path_flow) path_flow = residual[u][v];
        }

        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            residual[u][v] -= path_flow;
            residual[v][u] += path_flow;
        }
        
        max_flow += path_flow;
        printf(" -> 堆顶锁定巨型通道，推入流量: %d, 当前总流量: %d\n", path_flow, max_flow);
    }
    
    /* 打扫战场 */
    FreeMatrix(residual, V);
    free(parent);
    
    return max_flow;
}

/* ==========================================
 * 测试用例
 * ========================================== */
int main() {
    int V = 4;
    
    /* 动态创建初始图，再也不用担心 MAX_V 撑爆内存了 */
    int** graph = CreateMatrix(V);
    
    graph[0][1] = 1000; graph[0][2] = 1000;
    graph[1][2] = 1; 
    graph[1][3] = 1000; graph[2][3] = 1000;

    int maxFlow = MaxCapacityFlow_Heap(V, graph, 0, 3);
    
    printf("\n>>> 最终网络的最大流为: %d\n", maxFlow);
    
    FreeMatrix(graph, V);
    return 0;
}