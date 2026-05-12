#include "C:\Users\Lenovo\Desktop\programme\fds data structures and algorithums\disjoint set union\disjoint_set.h"
#include "../edge_list.h"
#include <stdio.h>
#include <stdlib.h>

// /* ==========================================
//  * 1. 边集图的基础操作
//  * ========================================== */

// /* 创建边集数组图 */
// EdgeGraph* CreateEdgeGraph(int V, int E) {
//     EdgeGraph* graph = (EdgeGraph*)malloc(sizeof(EdgeGraph));
//     if(!graph) return NULL;
//     graph->V = V;
//     graph->E = E;
//     graph->edgeCount = 0;
//     graph->edges = (Edge*)malloc(E * sizeof(Edge));
//     if(!graph->edges) {
//         free(graph);
//         return NULL;
//     }
//     return graph;
// }
// /* 向图中添加边 (方便测试时录入数据) */
// void AddEdgeToGraph(EdgeGraph* graph, int src, int dest, int weight) {
//     if (!graph || graph->edgeCount >= graph->E) return;
//     int i = graph->edgeCount;
//     graph->edges[i].src = src;
//     graph->edges[i].dest = dest;
//     graph->edges[i].weight = weight;
//     graph->edgeCount++;
// }
// /* 销毁图并释放内存 */
// void DestroyEdgeGraph(EdgeGraph* graph) {
//     if (!graph) return;
//     free(graph->edges);
//     free(graph);
// }


/* ==========================================
 * 2. Kruskal 最小生成树算法核心
 * ========================================== */

/* 内部回调函数：供 qsort 使用，按边权重从小到大 (升序) 排序 */
static int CompareEdges(const void* a, const void* b) {
    Edge* edgeA = (Edge*)a;
    Edge* edgeB = (Edge*)b;
    return edgeA->weight - edgeB->weight; // 升序排序
}

/* Kruskal 算法实现：返回最小生成树的总权重 */





// #include "edge_list.h"
// /* 引入你写好的并查集。相对路径基于：graph/Edge List/kruskal_mst.c 找外部的 disjoint set union */
// #include "../../disjoint set union/disjoint_set.h" 

// /* ==========================================
//  * 1. 边集图的基础操作
//  * ========================================== */

// /* 创建边集数组图 */
// EdgeGraph* CreateEdgeGraph(int V, int E) {
//     EdgeGraph* graph = (EdgeGraph*)malloc(sizeof(EdgeGraph));
//     if (!graph) return NULL;
    
//     graph->V = V;
//     graph->E = E;
//     graph->edgeCount = 0; /* 初始边数为0 */
//     graph->edges = (Edge*)malloc(E * sizeof(Edge));
    
//     return graph;
// }

// /* 向图中添加边 (方便测试时录入数据) */
// void AddEdgeToGraph(EdgeGraph* graph, int src, int dest, int weight) {
//     if (!graph || graph->edgeCount >= graph->E) return;
    
//     int i = graph->edgeCount;
//     graph->edges[i].src = src;
//     graph->edges[i].dest = dest;
//     graph->edges[i].weight = weight;
//     graph->edgeCount++;
// }

// /* 销毁图并释放内存 */
// void DestroyEdgeGraph(EdgeGraph* graph) {
//     if (!graph) return;
//     free(graph->edges);
//     free(graph);
// }

// /* ==========================================
//  * 2. Kruskal 最小生成树算法核心
//  * ========================================== */

// /* 内部回调函数：供 qsort 使用，按边权重从小到大 (升序) 排序 */
// static int CompareEdges(const void* a, const void* b) {
//     Edge* edgeA = (Edge*)a;
//     Edge* edgeB = (Edge*)b;
//     return edgeA->weight - edgeB->weight;
// }

// /* Kruskal 算法实现：返回最小生成树的总权重 */
// int KruskalMST(EdgeGraph* graph) {
//     if (!graph || graph->edgeCount == 0) return 0;

//     int V = graph->V;
//     int E = graph->edgeCount; // 使用实际添加的边数
//     Edge* edges = graph->edges;

//     /* 步骤 1：将所有边按权重从小到大排序，时间复杂度 O(E log E) */
//     qsort(edges, E, sizeof(Edge), CompareEdges);

//     /* 步骤 2：创建并查集。你的 disjoint_set.c 已经优雅地支持了 size+1 (1-based 索引) */
//     DisjointSet* ds = CreateDisjointSet(V);

//     int mstWeight = 0;   /* 记录最小生成树的总权重 */
//     int edgesAdded = 0;  /* 记录已经成功加入树的边数 */

//     printf("========== Kruskal MST 构建过程 ==========\n");

//     /* 步骤 3：贪心策略，从最便宜的边开始遍历 */
//     for (int i = 0; i < E; i++) {
//         int u = edges[i].src;
//         int v = edges[i].dest;
//         int weight = edges[i].weight;

//         /* 核心判断：如果起点 u 和终点 v 的根节点不同，说明它们不在同一个集合，加入该边【不会形成环】 */
//         if (Find(ds, u) != Find(ds, v)) {
//             /* 采用这条边！*/
//             printf("[采用] 边: %d -- %d \t权重: %d\n", u, v, weight);
//             mstWeight += weight;
//             Union(ds, u, v); /* 将这两个顶点的集合合并 */
//             edgesAdded++;

//             /* 优化机制：一棵 N 个顶点的树，刚好只有 N - 1 条边。达到此数量即可提前结束算法 */
//             if (edgesAdded == V - 1) {
//                 break;
//             }
//         } else {
//             /* 可选：如果你想看清楚哪些边因为会形成环而被抛弃，可以解除下面的注释 */
//             // printf("[抛弃] 边: %d -- %d \t权重: %d (会形成环)\n", u, v, weight);
//         }
//     }

//     printf("==========================================\n");
//     printf(">>> 最小生成树总权重: %d\n\n", mstWeight);

//     /* 清理并查集占用内存 */
//     DestroyDisjointSet(ds);

//     return mstWeight;
// }