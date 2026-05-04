#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "adj_list.h"

#define INF INT_MAX // 用最大整数代表无穷大

/* 对应幻灯片中的 Table 结构，用于记录算法运行状态 */
typedef struct VertexInfo {
    int dist;   /* 到源点的最短距离 */
    int known;  /* 是否已被处理 (1为是，0为否) */
    int path;   /* 记录前驱顶点，用于倒推路径 */
} VertexInfo;

/* 内部辅助函数：打印最终的距离和路径状态 */
void PrintTable(VertexInfo* table, int V, int startVertex) {
    printf("Vertex\tknown\tdist\tpath\n");
    for(int i = 0; i < V; i++) {
        printf("%d\t%d\t", i, table[i].known);
        if(table[i].dist == INF) {
            printf("INF\t");
        } else {
            printf("%d\t", table[i].dist);
        }
        
        if(table[i].path == -1) {
            printf("-\n");
        } else {
            printf("%d\n", table[i].path);
        }
    }
    printf("====================================\n");
}

/* 基础版无权最短路径 */
void UnweightedBasic(Graph* graph, int startVertex) {
    if(!graph || startVertex >= graph->V) return;

    int V = graph->V;
    VertexInfo* table = (VertexInfo*)malloc(V * sizeof(VertexInfo));
    if(!table) return;

    /* 初始化table */
    for(int i = 0; i < V; i++) {
        table[i].dist = INF;
        table[i].known = 0;
        table[i].path = -1;         /* -1 表示没有前驱 */
    }
    table[startVertex].dist = 0;    /* 起点到自己的距离为0 */

    /* 核心逻辑：按当前距离递增进行扫描 */
    for(int currDist = 0; currDist < V; currDist++) {
        for(int v = 0; v < V; v++) {
            /* 寻找未知且距离恰好等于 currDist 的顶点 */
            if(!table[v].known && table[v].dist == currDist){
                table[v].known = 1;

                /* 遍历该顶点的所有邻接点 (顺藤摸瓜) */
                AdjListNode* curr = graph->array[v].head;
                while(curr) {
                    int w = curr->dest;
                    if(table[w].dist == INF) {          /* 只更新未访问过的邻居 */
                        table[w].dist = currDist + 1;   /* 更新距离 */
                        table[w].path = v;              /* 记录前驱 */
                    }
                    curr = curr->next;
                }
            }
        }
    }
    printf("========== 基础版最短路径 (起点 %d) ==========\n", startVertex);
    PrintTable(table, V, startVertex);
    free(table);
}

/* 改进版无权最短路径 (使用数组模拟队列) */
void UnweightedOptimized(Graph* graph, int startVertex) {
    if(!graph || startVertex >= graph->V) return;

    int V = graph->V;
    VertexInfo* table = (VertexInfo*)malloc(V * sizeof(VertexInfo));
    if(!table) return;

    /* 初始化table */
    for(int i = 0; i < V; i++) {
        table[i].dist = INF;
        table[i].known = 0;
        table[i].path = -1;
    }
    table[startVertex].dist = 0;

    /*初始化数组模拟队列*/
    int* queue = (int*)malloc(V * sizeof(int));
    if(!queue) {
        free(table);
        return;
    }
    int rear = 0, front = 0;

    /* 将起点入队 */
    queue[rear++] = startVertex;

    /* 只要队列不为空(front < rear)*/
    while(front < rear) {
        int v = queue[front++];
        table[v].known = 1;

        /* 遍历该顶点的所有邻接点 */
        AdjListNode* curr = graph->array[v].head;
        while(curr) {
            int w = curr->dest;
            if(table[w].dist == INF) {          /* 只更新未访问过的邻居 */
                table[w].dist = table[v].dist + 1;   
                table[w].path = v;            
                /* 将新发现的邻居入队 */
                queue[rear++] = w;              
            }
            curr = curr->next;
        }
    }
    printf("========== 队列版最短路径 (起点 %d) ==========\n", startVertex);
    PrintTable(table, V, startVertex);
    
    free(queue);
    free(table);
}
    
