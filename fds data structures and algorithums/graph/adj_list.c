#include <stdio.h>
#include <stdlib.h>
#include "adj_list.h"

/*内部辅助函数：创建一个新的边节点 (设为 static，不对外暴露)*/
static AdjListNode* CreateNode(int dest) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    if(!newNode) return NULL;
    newNode->dest = dest;
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

/*添加无向边 (头插法)*/
void AddEdge(Graph* graph, int src, int dest) {
    if (!graph || src >= graph->V || dest >= graph->V) return;

    /*动作1: dest 挂到 src 的链表*/
    AdjListNode* newNode = CreateNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    /*动作2: src 挂到 dest 的链表 (无向图)*/
    newNode = CreateNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

void PrintGraph(Graph* graph) {
    if (!graph) return;
    printf("========== 传统邻接表状态 ==========\n");
    for(int v = 0; v < graph->V; v++) {
        AdjListNode* curr = graph->array[v].head;
        printf("Vertex %d:", v);
        while(curr) {
            printf(" -> %d", curr->dest);
            curr = curr->next;
        }
        printf("\n");
    }
    printf("====================================\n");
}\

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