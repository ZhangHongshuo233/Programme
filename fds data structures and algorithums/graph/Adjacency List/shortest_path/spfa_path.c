#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "../adj_list.h"

#define INF (INT_MAX >> 1)

/* 内部辅助函数：打印结果 */
static void PrintResult(int V, int startVertex, int* dist, int* path) {
    printf("========== SPFA 最短路径 (起点 %d) ==========\n", startVertex);
    printf("Vertex\tDist\tPath(前驱)\n");
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
    printf("=============================================\n\n");
}

/* * SPFA 算法核心实现 (Shortest Path Faster Algorithm)
 * 时间复杂度: O(E) 在平均情况下，最坏情况下为 O(VE)
 * 空间复杂度: O(V) 用于存储距离、路径和队列状态
 * 参数: graph (邻接表图), startVertex (起点编号)
 * 返回值: 如果图中存在从起点可达的负权环，返回 false；否则返回 true
 */

bool SPFA(Graph* graph, int startVertex) {
    if(!graph || startVertex < 1 || startVertex > graph->V) return false;

    int V = graph->V;

    /* 1. 分配核心状态数组 (1-based 索引，大小开 V+1) */
    int* dist = (int*)malloc((V+1)*sizeof(int));
    int* path = (int*)malloc((V+1)*sizeof(int));
    bool* inQueue = (bool*)calloc(V+1, sizeof(bool));   /* 初始化为 false */
    int* cnt = (int*)calloc(V+1, sizeof(int));          /* 负权环检测计数器 */

    /* 初始化 */
    for(int i = 1; i <= V; i++) {
        dist[i] = INF;
        path[i] = -1;
    }
    dist[startVertex] = 0;

    /* 2. 创建环形队列 (最大容量设为 V+2 即可保证绝对安全) */
    int capacity = V + 2;
    int* queue = (int*)malloc(capacity * sizeof(int));
    int front = 0, rear = 0;

    /* 起点入队*/
    queue[rear++ % capacity] = startVertex;
    inQueue[startVertex] = true;
    cnt[startVertex]++;

    /* 3. SPFA 算法主循环 */
    while(front != rear){
        int u = queue[front++ % capacity];
        inQueue[u] = false;     /* 标记为不在队列中，未来如果有更短的路径，可以再次入队 */

        /* 遍历该顶点的所有邻接点 */
        AdjListNode* curr = graph->array[u].head;
        while(curr) {
            int v = curr->dest;
            int w = curr->weight;

            /* 松弛操作：如果借道 u 让到达 v 的距离变短了 */
            if(dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                path[v] = u;

                /* 如果被更新的邻居 v 目前不在队列里，就把它塞进队列 */
                if(!inQueue[v]) {
                    queue[rear++ % capacity] = v;
                    inQueue[v] = true;
                    cnt[v]++;
                }

                /* 负权环排雷机制：统计入队次数 */
                if(cnt[v] >= V) {
                    /* 任何一个节点入队次数达到 V 次，绝对是陷入了负权环！*/
                    printf("\n[警告] SPFA 检测到图中存在从起点可达的负权环！\n");
                    free(dist); free(path); free(inQueue); free(cnt); free(queue);
                    return false;
                }
            }

            curr = curr->next;
        }
    }

    /* 4. 正常结束，打印最短路径表 */
    PrintResult(V, startVertex, dist, path);

    /* 释放内存 */
    free(dist); free(path); free(inQueue); free(cnt);free(queue);
    return true;
}

/* ==========================================
 * 测试主函数
 * ========================================== */
int main() {
    /* ===================================================
     * 测试用例 1：带负权边，但没有负权环的有向图
     * =================================================== */
    printf("【测试用例 1】正常的带负权边有向图\n");
    int V1 = 5; 
    Graph* graph1 = CreateGraph(V1);

    /* 注意：你的 AddDirectedEdge 默认可能是无向的。
     * 对于含有负权边的图，必须当做有向图测试！
     * 请确保你的 adj_list.c 里的 AddDirectedEdge 只执行了单向挂载 (src -> dest)
     * 或者在 AddDirectedEdge 中通过修改/传递参数来控制。
     * 这里假设你的 AddDirectedEdge 是单向有向边。 */
    AddDirectedEdge(graph1, 1, 2, -1);
    AddDirectedEdge(graph1, 1, 3, 4);
    AddDirectedEdge(graph1, 2, 3, 3);
    AddDirectedEdge(graph1, 2, 4, 2);
    AddDirectedEdge(graph1, 2, 5, 2);
    AddDirectedEdge(graph1, 4, 2, 1);
    AddDirectedEdge(graph1, 4, 3, 5);
    AddDirectedEdge(graph1, 5, 4, -3);

    SPFA(graph1, 1);
    DestroyGraph(graph1);


    /* ===================================================
     * 测试用例 2：图中存在负权环
     * =================================================== */
    printf("【测试用例 2】带有负权环的图\n");
    int V2 = 4;
    Graph* graph2 = CreateGraph(V2);

    AddDirectedEdge(graph2, 1, 2, 4);
    AddDirectedEdge(graph2, 1, 3, 5);
    AddDirectedEdge(graph2, 3, 4, 3);
    
    /* 制造一个负权环: 2 -> 3 (-6) -> 2 (2) ，环路总权值为 -4 */
    AddDirectedEdge(graph2, 2, 3, -6);
    AddDirectedEdge(graph2, 3, 2, 2); 

    SPFA(graph2, 1);
    DestroyGraph(graph2);

    return 0;
}