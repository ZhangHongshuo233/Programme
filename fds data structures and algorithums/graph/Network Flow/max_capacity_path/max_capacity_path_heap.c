#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "C:\Users\Lenovo\Desktop\programme\fds data structures and algorithums\heap\binary heap\min_heap\min_heap.h"
#define MAX_V 1000
#define INF 1000000000

/* ==========================================
 * 单次寻路：基于外挂最小堆优化的魔改 Dijkstra
 * 核心魔法：向最小堆 Push 负数容量，从而实现最大堆的效果
 * 时间复杂度：O(E log V)
 * ========================================== */
bool dijkstra_max_cap_heap(int V, int residual[MAX_V][MAX_V], int s, int t, int parent[]) {
    int max_cap[MAX_V];
    
    /* 1. 初始化 */
    for (int i = 0; i < V; i++) {
        max_cap[i] = 0;
        parent[i] = -1;
    }
    max_cap[s] = INF;

    /* 初始化你的最小堆，容量开到足够大 (比如 E 级别，这里用 V*V 兜底) */
    MinHeap* H = CreateMinHeap(V * V);
    
    /* 🌟 魔法操作：源点拥有无穷大的水，取负数后变为 -INF 压入最小堆！ */
    Push(H, s, -INF);

    /* 2. 核心大循环 */
    while (!IsEmpty(H)) {
        /* 弹出最小堆的堆顶 (也就是负得最多的，绝对值/正数容量最大的那个) */
        HeapNode current = Pop(H);
        int u = current.vertex;
        
        /* 还原真实的瓶颈容量大小 */
        int current_real_cap = -current.dist;

        /* 🌟 懒惰删除法 (Lazy Deletion)
         * 如果弹出来的这个数据的容量，比当前数组里记录的最新 max_cap 还要小，
         * 说明这是一条历史遗留的"废数据"，直接跳过！*/
        if (current_real_cap < max_cap[u]) continue;

        /* 如果已经锁定了到达终点的最大管子，提前下班 */
        if (u == t) break; 

        /* 3. 遍历邻居并更新 */
        for (int v = 0; v < V; v++) {
            if (residual[u][v] > 0) {
                /* 木桶效应：计算到达 v 的潜在瓶颈容量 */
                int new_cap = (max_cap[u] < residual[u][v]) ? max_cap[u] : residual[u][v];
                
                /* 贪心操作：如果发现了更粗的路径 */
                if (new_cap > max_cap[v]) {
                    max_cap[v] = new_cap;
                    parent[v] = u;
                    
                    /* 再次使用魔法：将新发现的容量取负数后压入最小堆 */
                    Push(H, v, -new_cap);
                }
            }
        }
    }
    
    /* 养成好习惯，释放堆内存，防止内存泄漏 */
    DestroyMinHeap(H); 
    return max_cap[t] > 0;
}

/* ==========================================
 * 核心：最大容量路径网络流主函数
 * ========================================== */
int MaxCapacityFlow_Heap(int V, int graph[MAX_V][MAX_V], int s, int t) {
    int residual[MAX_V][MAX_V];
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            residual[i][j] = graph[i][j];
        }
    }

    int parent[MAX_V];
    int max_flow = 0;

    printf("=== 极客版：调用自有 MinHeap API 实现的最大容量增广路 ===\n");
    
    /* 只要还能找到管子，就一直压榨 */
    while (dijkstra_max_cap_heap(V, residual, s, t, parent)) {
        int path_flow = INF;
        
        /* 回溯找出这条路径上的最终瓶颈 */
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            if (residual[u][v] < path_flow) path_flow = residual[u][v];
        }

        /* 建立残量图：正向减流量，反向加流量 (允许反悔) */
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            residual[u][v] -= path_flow;
            residual[v][u] += path_flow;
        }
        
        max_flow += path_flow;
        printf(" -> 堆顶锁定巨型通道，推入流量: %d, 当前总流量: %d\n", path_flow, max_flow);
    }
    return max_flow;
}

/* ==========================================
 * 测试用例
 * ========================================== */
int main() {
    int V = 4;
    int graph[MAX_V][MAX_V] = {0};
    
    /* 构造 PPT 中的那个杀手图变体：
     * S(0), A(1), B(2), T(3)
     * 有两条容量为 1000 的大路，中间夹着一条容量为 1 的细管子 
     */
    graph[0][1] = 1000; graph[0][2] = 1000;
    graph[1][2] = 1; 
    graph[1][3] = 1000; graph[2][3] = 1000;

    int maxFlow = MaxCapacityFlow_Heap(V, graph, 0, 3);
    
    printf("\n>>> 最终网络的最大流为: %d\n", maxFlow);
    return 0;
}