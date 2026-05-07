#ifndef SHORTEST_PATH_H
#define SHORTEST_PATH_H

#include "adj_list.h"
#include <limits.h>

#define INF INT_MAX

/* 统一的路径状态表结构 */
typedef struct VertexInfo {
    int dist;   /* 到源点的最短距离 */
    int known;  /* 是否已被处理 (1为是，0为否) */
    int path;   /* 记录前驱顶点，用于倒推路径 */
} VertexInfo;

/* 暴露给所有算法的打印函数 */
void PrintTable(VertexInfo* table, int V, int startVertex, const char* algoName);

/* 你的无权算法接口 */
void UnweightedBasic(Graph* graph, int startVertex);
void UnweightedOptimized(Graph* graph, int startVertex);

void DijkstraBasic(Graph* graph, int startVertex);
void DijkstraOptimized(Graph* graph, int startVertex);

#endif // SHORTEST_PATH_H