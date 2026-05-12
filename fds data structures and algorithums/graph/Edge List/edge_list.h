#ifndef EDGE_LIST_H 
#define EDGE_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF (INT_MAX >> 1)

typedef struct Edge {
    int src;
    int dest;
    int weight;
}Edge;

/* 定义基于边集数组的图 (专为 Kruskal 算法设计) */
typedef struct EdgeGraph {
    int V;          /* 顶点数 */
    int E;          /* 边数容量 */
    int edgeCount;  /* 当前实际已添加的边数 */
    Edge* edges;    /* 存储所有边的动态数组 */
} EdgeGraph;

/* API 接口声明 */
EdgeGraph* CreateEdgeGraph(int V, int E);
void AddEdgeToGraph(EdgeGraph* graph, int src, int dest, int weight);
void DestroyEdgeGraph(EdgeGraph* graph);

/* Kruskal 算法接口 */
int KruskalMST(EdgeGraph* graph);

#endif // EDGE_LIST_H