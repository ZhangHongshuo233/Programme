#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../adj_list.h"
#include "../../../heap/binary heap/min_heap/min_heap.h"
#include <limits.h>

#define INF (INT_MAX>>1)

/********************
 * Prim 最小生成树算法核心
 ********************/
int PrimMST(Graph* graph, int startVertex) {
    if(!graph || startVertex < 0 || startVertex >= graph->V) return -1;

    int V = graph->V;
    int* parent = (int*)malloc((V + 1) * sizeof(int));
    int* cost = (int*)malloc((V + 1) * sizeof(int));
    bool* visited = (bool*)calloc(V + 1, sizeof(bool));

    /* 初始化 */
    for(int i = 0; i < V; i++) {
        cost[i] = INF;
        parent[i] = -1;
    }

    /* 树根的代价为 0 */
    cost[startVertex] = 0;

    /* 由于采用懒惰删除，同一个节点可能被多次 Push 进堆。
       最大入队次数可能达到边数 E，所以容量必须开 V * V */
    MinHeap* H = CreateMinHeap(V * V);
    Push(H, startVertex, cost[startVertex]);    

    int total_cost = 0;
    int edges_added = 0;

    printf("========== Prim 算法生成过程 ==========\n");

    /* 只要堆不为空，并且还没有收集够 V-1 条边 */
    while(!IsEmpty(H)) {
        HeapNode curr = Pop(H);
        int u = curr.vertex;

        /*懒惰删除：如果这个节点已经在树里了，说明这是旧数据，直接丢弃*/
        if(u < 0 || u >= V || visited[u]) continue;

        /* 标记该节点已加入树中 */
        visited[u] = true;
        total_cost += cost[u];

        /* 输出当前加入树的节点和边的代价 */
        if(parent[u] != -1) {
            printf("加入边 (%d, %d) 代价: %d\n", parent[u], u, cost[u]);
            edges_added++;
        } else {
            printf("加入起点 %d\n", u);
        }

        /* 遍历 u 的邻接点，看看是否可以更新最小代价 */
        AdjListNode* node = graph->array[u].head;
        while(node) {
            int v = node->dest;
            int w = node->weight;

            /* 核心逻辑：如果 v 不在树中，且 u-v 的边比之前记录的接入代价还要便宜！
               (这就是和 Dijkstra 唯一的区别：这里不累加 u 之前的距离，只看单条边) */
            if(!visited[v] && w < cost[v]) {
                cost[v] = w;
                parent[v] = u;
                Push(H, v, cost[v]);
            }

            node = node->next;
        }
    }

    printf("========================================\n");

    /* 安全性检查：如果图不是连通的，MST 是不存在的 */
    if(edges_added != V - 1) {
        printf("[警告] 图不连通！无法生成覆盖所有顶点的最小生成树。\n");
    } else {
        printf(">>> 最小生成树 (MST) 总造价: %d\n", total_cost);
    }

    /* 释放内存 */
    free(parent);
    free(cost);
    free(visited);
    DestroyMinHeap(H);

    return total_cost;
}

/********************
 * 测试主函数
 ********************/
int main() {
    int V = 7; 
    Graph* graph = CreateGraph(V);

    /* 录入课件 PPT 中的无向连通图数据 */
    AddEdge(graph, 0, 1, 2);
    AddEdge(graph, 0, 2, 4);
    AddEdge(graph, 0, 3, 1);
    AddEdge(graph, 1, 3, 3);
    AddEdge(graph, 1, 4, 10);
    AddEdge(graph, 2, 3, 2);
    AddEdge(graph, 2, 5, 5);
    AddEdge(graph, 3, 4, 7);
    AddEdge(graph, 3, 5, 8);
    AddEdge(graph, 3, 6, 4);
    AddEdge(graph, 4, 6, 6);
    AddEdge(graph, 5, 6, 1);

    PrimMST(graph, 0);

    DestroyGraph(graph);
    return 0;
}