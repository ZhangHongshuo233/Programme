#include <stdio.h>
#include <stdlib.h>
#include "adj_multilist.h"

AdjMultilist* CreateMultilist(int V) {
    AdjMultilist* graph = (AdjMultilist*)malloc(sizeof(AdjMultilist));
    graph->numVertices = V;
    graph->numEdges = 0;
    graph->array = (VertexNode*)malloc(V * sizeof(VertexNode));

    for(int i = 0; i < V; i++) {
        graph->array[i].data = i;
        graph->array[i].firstedge = NULL;
    }
    return graph;
}

void AddEdge(AdjMultilist* graph, int src, int dest) {
    if (!graph || src >= graph->numVertices || dest >= graph->numVertices) return;

    EdgeNode* edge = (EdgeNode*)malloc(sizeof(EdgeNode));
    if(!edge) return;

    edge->mark = 0;
    edge->ivex = src;
    edge->jvex = dest;
    
    /* 将边头插到 src 顶点的链表中*/
    edge->ilink = graph->array[src].firstedge;
    graph->array[src].firstedge = edge;

    /* 将边头插到 dest 顶点的链表中*/
    edge->jlink = graph->array[dest].firstedge;
    graph->array[dest].firstedge = edge;

    graph->numEdges++;
}

// 打印所有物理存在的边 (展示多重表的优势：每条边只会被处理一次)
void PrintMultilistEdges(AdjMultilist* graph) {
    if (!graph) return;
    printf("========== 邻接多重表：全局边库 ==========\n");
    // 重置所有边的 mark 为 0 (防御性编程)
    // 实际工业中，通常在遍历时通过 mark 来防重
    
    int edgeCount = 1;
    for (int i = 0; i < graph->numVertices; i++) {
        EdgeNode* curr = graph->array[i].firstedge;
        while (curr != NULL) {
            // 只有当这条边没有被打印过时，才打印它
            if (curr->mark == 0) {
                printf("物理边 %d: [顶点 %d <---> 顶点 %d]\n", edgeCount++, curr->ivex, curr->jvex);
                curr->mark = 1; // 标记为已处理
            }
            
            // 顺藤摸瓜：根据当前是从哪个顶点过来的，决定走哪条 link
            if (curr->ivex == i) {
                curr = curr->ilink;
            } else {
                curr = curr->jlink;
            }
        }
    }
    printf("共统计到 %d 条物理边。\n", graph->numEdges);
    printf("==========================================\n");
}

// 释放多重表内存 (极其考验内功的一环)
void DestroyMultilist(AdjMultilist* graph) {
    if (!graph) return;
    
    // 释放多重表的边需要特别小心，因为一条边被两个顶点共享。
    // 绝不能对同一块内存 free 两次 (Use-After-Free 漏洞)。
    // 这里使用一个数学取巧：只在顶点的编号等于边的最小编号时，才释放它。
    for (int i = 0; i < graph->numVertices; i++) {
        EdgeNode* curr = graph->array[i].firstedge;
        while (curr != NULL) {
            EdgeNode* next;
            // 找出下一条边
            if (curr->ivex == i) next = curr->ilink;
            else next = curr->jlink;

            // 比较巧妙的安全释放法：只由编号较小的顶点负责释放这条边的内存
            // 这样就能保证一条边绝对只会被 free 一次，且无需依赖 mark
            int min_vex = (curr->ivex < curr->jvex) ? curr->ivex : curr->jvex;
            if (min_vex == i) {
                free(curr); 
            }
            curr = next;
        }
    }
    free(graph->array);
    free(graph);
}