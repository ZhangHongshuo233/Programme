#ifndef ADJ_MULTILIST_H
#define ADJ_MULTILIST_H

#include <stdio.h>
#include <stdlib.h>

// 边节点 (一仆二主)
typedef struct EdgeNode {
    int mark;               // 标志域：0表示未访问，1表示已访问/处理
    int ivex;               // 边依附的第一个顶点
    int jvex;               // 边依附的第二个顶点
    struct EdgeNode* ilink; // 指向依附于 ivex 的下一条边
    struct EdgeNode* jlink; // 指向依附于 jvex 的下一条边
} EdgeNode;

// 顶点节点
typedef struct VertexNode {
    int data;               // 顶点的数据 (这里可以存大侠的战力等，暂存顶点编号)
    EdgeNode* firstedge;    // 挂靠在此顶点的第一条边
} VertexNode;
 
// 图本体
typedef struct AdjMultilist {
    int numVertices;
    int numEdges;
    VertexNode* array;      // 动态分配的顶点数组
} AdjMultilist;

//API
AdjMultilist* CreateMultilist(int vertices);
void AddMultiEdge(AdjMultilist* G, int src, int dest);
void PrintMultilistEdges(AdjMultilist* G);
void DestroyMultilist(AdjMultilist* G);

#endif // ADJ_MULTILIST_H