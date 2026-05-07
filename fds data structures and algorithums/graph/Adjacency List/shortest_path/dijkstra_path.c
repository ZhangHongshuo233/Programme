#include <stdio.h>
#include <stdlib.h>
#include "C:\Users\Lenovo\Desktop\programme\fds data structures and algorithums\heap\binary heap\min_heap\min_heap.h"
#include "shortest_path.h"

void DijkstraBasic(Graph* graph, int startVertex) {
    if(!graph || startVertex < 0 || startVertex >= graph->V) return;

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

    /* 寻找最小距离节点 V 次 */
    for(int count = 0; count < V; count++) {
        int v = -1;
        int minDist = INF;

        /* 在所有未处理顶点中，扫描找最小 */
        for(int i = 0; i < V; i++) {
            if(!table[i].known && table[i].dist <= minDist) {
                minDist = table[i].dist;
                v = i;
            }
        }

        /* 找不到可达的有效顶点（剩下的全是不连通的孤岛），提前结束 */
        if (v == -1 || minDist == INF) break;

        table[v].known = 1;

        /* 遍历该顶点的所有邻接点 (执行 Decrease 操作) */
        AdjListNode* curr = graph->array[v].head;\
        while(curr) {
            int w = curr->dest;
            int weight = curr->weight;

            /* 如果 w 未被确定，并且借道 v 能够缩短距离 */
            if(!table[w].known && table[v].dist + weight < table[w].dist) {
                table[w].dist = table[v].dist + weight;
                table[w].path = v;
            }

            curr = curr->next;
        }
    }

    PrintTable(table, V, startVertex, "DijkstraBasic");
    free(table);
}

/* 改进版 Dijkstra：使用最小堆优化，适用于稀疏图 O(|E|log|V|) */
void DijkstraOptimized(Graph* graph, int startVertex) {
    if(!graph || startVertex < 0 || startVertex >= graph->V) return;

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

    /* 
     * 初始化最小堆 
     * 容量需要 |E| 的空间，最坏情况容量可以设为 V*V 
     */
    int capacity = V * V;
    MinHeap* minHeap = CreateMinHeap(capacity);
    if(!minHeap) {
        free(table);
        return;
    }

    /* 起点入堆 */
    Push(minHeap, startVertex, 0);

    while(minHeap->size > 0) {
        /* 从堆顶抽出当前最小距离的节点 */
        HeapNode minNode = Pop(minHeap);
        int v = minNode.vertex;

        /* 【核心机制】：
         * 如果这个顶点之前已经被确定过了 (known == 1)，
         * 说明这是堆里面残留的旧数据，直接丢弃，继续 Pop！
         */
        if(table[v].known) continue;
        
        table[v].known = 1;

        /* 遍历该顶点的所有邻接点 */
        AdjListNode* curr = graph->array[v].head;
        while(curr) {
            int w = curr->dest;
            int weight = curr->weight;

            if(!table[w].known && table[v].dist + weight < table[w].dist) {
                table[w].dist = table[v].dist + weight;
                table[w].path = v;

                /* 将更新后的节点及距离直接压入堆中 */
                Push(minHeap, w, table[w].dist);
            }

            curr = curr->next;
        }
    }
    
    PrintTable(table, V, startVertex, "DijkstraOptimized");
    DestroyMinHeap(minHeap);
    free(table);
}  

/* * 判断给定的顶点序列 seq 是否为合法的 Dijkstra 序列
 * graph: 你的加权图指针
 * seq: 待验证的顶点数组
 * seqLen: 序列的长度 (通常等于顶点数 V)
 * 返回值: 1 表示合法，0 表示非法
 */
int IsDijkstraSequence(Graph* graph, int* seq, int seqLen) {
    if(!graph || !seq || seqLen > graph->V || seqLen <= 0) return 0;

    int V = graph->V;
    int* dist = (int*)malloc(V * sizeof(int));
    int* visited = (int*)calloc(V, sizeof(int));

    if(!dist || !visited) return 0;

    /* 1. 初始化距离表，全部设为无穷大 */
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
    }

    /* 2. 序列的第一个顶点就是起点，距离设为 0 */
    dist[seq[0]] = 0;

    /* 3. 按照序列顺序，逐个验证 */
    for(int i = 0; i < seqLen; i++) {
        int v = seq[i];

        /* 错误情况1：该节点已经被访问过了 (序列里有重复节点) */
        if(visited[v]) {
            free(dist);
            free(visited);
            return 0;
        }

        visited[v] = 1;

        /* 动作1：在所有未访问的节点中，找出当前的最小距离 */
        int minDist = INF;
        for(int j = 0; j < V; j++) {
            if(!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
            }
        }

        /* 动作2：严格审查！
         * 如果当前节点 v 的距离大于全场的最小距离，说明它“插队”了！违背贪心原则。 */
        if(dist[v] > minDist) {
            free(dist);
            free(visited);
            return 0;   /* 验证失败，不是 Dijkstra 序列 */
        }

        /* 动作3：顺藤摸瓜，松弛它的所有邻居 */
        AdjListNode* curr = graph->array[v].head;
        while(curr) {
            int w = curr->dest;
            int weight = curr->weight;

            /* 注意防范 dist[v] 是 INF 时的整数溢出 */
            if(!visited[w] && dist[v] != INF && dist[v] + weight < dist[w]) {
                dist[w] = dist[v] + weight;
            }
            curr = curr->next;
        }
    }
    /* 如果整个序列都顺利扛过了审查，那就是合法的！ */
    free(dist); 
    free(visited);
    return 1;    
}
