#include <stdio.h>
#include <stdlib.h> 
#include "edge_list.h"

/* 创建边集数组图 */
EdgeGraph* CreateEdgeGraph(int V, int E) {
    EdgeGraph* graph = (EdgeGraph*)malloc(sizeof(EdgeGraph));
    if(!graph) return NULL;

    graph->V = V;
    graph->E = E;
    graph->edgeCount = 0;
    graph->edges = (Edge*)malloc(E * sizeof(Edge));
    if(!graph->edges) {
        free(graph);
        return NULL;
    }
    return graph;
}

/* 向图中添加边 (方便测试时录入数据) */
void AddEdgeToGraph(EdgeGraph* graph, int src, int dest, int weight) {
    if (!graph || graph->edgeCount >= graph->E) return;
    
    int i = graph->edgeCount;
    graph->edges[i].src = src;
    graph->edges[i].dest = dest;
    graph->edges[i].weight = weight;
    graph->edgeCount++;
}

/* 销毁图并释放内存 */
void DestroyEdgeGraph(EdgeGraph* graph) {
    if (!graph) return;
    free(graph->edges);
    free(graph);
}


