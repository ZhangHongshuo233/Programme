#include <stdio.h>
#include <stdlib.h>
#include "edge_list.h"
#include <stdbool.h>

/* 内部辅助函数：打印最终的距离和路径状态 */
static void PrintResult(int V, int startVertex, int* dist, int* path) {
    printf("========== Bellman-Ford 最短路径 (起点 %d) ==========\n", startVertex);
    printf("Vertex\tDist\tPath(前驱)\n");
    /* 假设顶点编号是从 1 到 V */
    for (int i = 1; i <= V; i++) {
        printf("%d\t", i);
        if (dist[i] == INF) {
            printf("INF\t");
        } else {
            printf("%d\t", dist[i]);
        }
        
        if (path[i] == -1) {
            printf("-\n");
        } else {
            printf("%d\n", path[i]);
        }
    }
    printf("=====================================================\n\n");
}


/* * Bellman-Ford 算法核心实现
 * 参数: graph (边集图), startVertex (起点编号)
 * 返回值: 如果图中存在从起点可达的负权环，返回 false；否则返回 true
 */

bool BellmanFord(EdgeGraph* graph, int startVertex) {
    if(!graph || graph->edgeCount == 0) return false;

    int V = graph->V;
    int E = graph->edgeCount;
    Edge* edges = graph->edges;

    /* 为距离表和前驱表分配内存 (1-based 索引，所以开 V + 1) */
    int* dist = (int*)malloc((V + 1) * sizeof(int));
    int* path = (int*)malloc((V + 1) * sizeof(int));

    /* 步骤 1：初始化 */
    for(int i = 1; i <= V; i++) {
        dist[i] = INF;
        path[i] = -1;
    }
    dist[startVertex] = 0;

    /* 步骤 2：核心大循环，执行 V - 1 轮全面松弛 */
    for(int i = 1; i <= V - 1; i++) {
        bool updated = false; /* 优化：如果某轮没有任何节点被更新，可以提前结束 */
        
        for(int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;

            /* 如果 u 是可达的，并且借道 u 可以让 v 更近 */
            if(dist[u] != INF && dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                path[v] = u;
                updated = true;
            }
        }

        /* 如果在这一轮中没有任何顶点的距离被缩短，说明最短路径已经提前找齐了 */
        if(!updated) break;
    }

    /* 步骤 3：第 V 轮，检测负权环 */
    for(int j = 0; j < E; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int w = edges[j].weight;

        if(dist[u] != INF && dist[u] + w < dist[v]) {
            printf("\n[警告] 图中存在从起点可达的负权环！最短路径不存在！\n");
            free(dist);
            free(path); 
            return false;
        }
    }

    /* 步骤 4：一切正常，打印结果 */
    PrintResult(V, startVertex, dist, path);

    free(dist);
    free(path);
    return true;
}


int main() {
    /* ===================================================
     * 测试用例 1：带负权边，但没有负权环的正常有向图
     * =================================================== */
    printf("【测试用例 1】正常的带负权边有向图\n");
    int V1 = 5; 
    int E1 = 8;
    EdgeGraph* graph1 = CreateEdgeGraph(V1, E1);

    /* 添加有向边 (注意：Bellman-Ford 遇到负权边时，图通常是有向的) */
    AddEdgeToGraph(graph1, 1, 2, -1);
    AddEdgeToGraph(graph1, 1, 3, 4);
    AddEdgeToGraph(graph1, 2, 3, 3);
    AddEdgeToGraph(graph1, 2, 4, 2);
    AddEdgeToGraph(graph1, 2, 5, 2);
    AddEdgeToGraph(graph1, 4, 2, 1);
    AddEdgeToGraph(graph1, 4, 3, 5);
    AddEdgeToGraph(graph1, 5, 4, -3);

    /* 以顶点 1 为起点运行 */
    BellmanFord(graph1, 1);
    DestroyEdgeGraph(graph1);


    /* ===================================================
     * 测试用例 2：图中存在负权环
     * =================================================== */
    printf("【测试用例 2】带有负权环的图\n");
    int V2 = 4;
    int E2 = 4;
    EdgeGraph* graph2 = CreateEdgeGraph(V2, E2);

    AddEdgeToGraph(graph2, 1, 2, 4);
    AddEdgeToGraph(graph2, 1, 3, 5);
    AddEdgeToGraph(graph2, 3, 4, 3);
    
    /* 制造一个负权环: 2 -> 3 -> 4 -> 2 (权重分别是 ? 这里简化为 2 和 4 之间互相负权重) */
    AddEdgeToGraph(graph2, 2, 3, -6);
    AddEdgeToGraph(graph2, 3, 2, 2); /* 2->3 (-6), 3->2 (2)，构成环路权重为 -4 */

    BellmanFord(graph2, 1);
    DestroyEdgeGraph(graph2);

    return 0;
}