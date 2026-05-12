#include <stdio.h>
#include <stdlib.h>
#include "adj_list.h"

/*内部辅助函数：创建一个新的边节点 (增加 weight 参数)*/
static AdjListNode* CreateNode(int dest, int weight) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    if(!newNode) return NULL;
    newNode->dest = dest;
    newNode->weight = weight;  /* 记录边的权重 */
    newNode->next = NULL;
    return newNode;
}

Graph* CreateGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if(!graph) return NULL;
    graph->V = V;
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));
    if(!graph->array) {
        free(graph);
        return NULL;
    }
    for(int i = 0; i < V; i++) {
        graph->array[i].head = NULL;
    }   
    return graph;
}

/*添加无向边/有向边 (头插法，增加 weight 参数)*/
void AddEdge(Graph* graph, int src, int dest, int weight) {
    if (!graph || src >= graph->V || dest >= graph->V) return;

    /*动作1: dest 挂到 src 的链表 (前向边)*/
    AdjListNode* newNode = CreateNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    /*动作2: src 挂到 dest 的链表 (无向图)
     * 注意：如果你的 Dijkstra 是为了测试有向图，请将下面这三行注释掉！
     * 如果是测试无向网，则保留。
     */
    newNode = CreateNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

void PrintGraph(Graph* graph) {
    if (!graph) return;
    printf("========== 加权邻接表状态 ==========\n");
    for(int v = 0; v < graph->V; v++) {
        AdjListNode* curr = graph->array[v].head;
        printf("Vertex %d:", v);
        while(curr) {
            /* 打印时带上权重，格式为 -> 目标点(权重) */
            printf(" -> %d(w:%d)", curr->dest, curr->weight);
            curr = curr->next;
        }
        printf("\n");
    }
    printf("====================================\n");
}

void DestroyGraph(Graph* graph) {
    if(!graph) return;
    for(int v = 0; v < graph->V; v++) {
        AdjListNode* curr = graph->array[v].head;
        while(curr) {
            AdjListNode* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(graph->array);
    free(graph);
}

/* 添加有向加权边 */
void AddDirectedEdge(Graph* graph, int src, int dest, int weight) {
    if (!graph || src >= graph->V || dest >= graph->V) return;

    /* 只有 src -> dest，没有 dest -> src */
    AdjListNode* newNode = CreateNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}