#ifndef ADJ_LIST_H
#define ADJ_LIST_H

#include <stdio.h>
#include <stdlib.h>

/* 链表节点：代表一条边 (现已支持加权) */
typedef struct AdjListNode {
    int dest;
    int weight;                 /* 新增：边的权重 */
    struct AdjListNode* next;
} AdjListNode;

/* 顶点表头 */
typedef struct AdjList {
    AdjListNode* head;  /* 链表头指针，指向第一个邻接节点 */
} AdjList;

/* 图本体 */
typedef struct Graph {
    int V;          /* 顶点数 */
    AdjList* array; /* 动态数组，存储所有顶点的表头 */
} Graph;

/* API */
Graph* CreateGraph(int V);
/* 注意：AddEdge 增加了 weight 参数 */
void AddEdge(Graph* graph, int src, int dest, int weight);
void PrintGraph(Graph* graph);
void DestroyGraph(Graph* graph);

#endif // ADJ_LIST_H