#include <stdio.h>
#include <stdlib.h>
#include "../adj_list.h"

/* 核心函数：关键路径法 (CPM)
 * 打印每个事件的 EC, LC，以及关键路径上的活动
 */
void CriticalPathMethod(Graph* graph) {
    if(!graph) return;

    int V = graph->V;
    int* inDegree = (int*)calloc(V + 1, sizeof(int));
    int* EC = (int*)calloc((V + 1), sizeof(int)); /*最早发生时间 */
    int* LC = (int*)malloc((V + 1) * sizeof(int)); /* 最迟发生时间 */
    int* topOrder = (int*)malloc((V + 1) * sizeof(int)); /* 存储拓扑序列，用于倒推 */

    /* 1. 统计所有顶点的入度 */
    for(int i = 1; i <= V; i++) {
        AdjListNode* curr = graph->array[i].head;
        while(curr) {
            inDegree[curr->dest]++;
            curr = curr->next;
        }
    }

    /* 2. 准备队列进行拓扑排序 */
    int* queue = (int*)malloc((V + 1) * sizeof(int));
    int front = 0, rear = 0;

    /* 将入度为 0 的顶点入队 (项目起点) */
    for (int i = 1; i <= V; i++) {
        if (inDegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    /* ==========================================
     * 第一阶段：前向传递 (Forward Pass) 算 EC
     * ========================================== */
    int topIndex = 0; /* 用于记录拓扑序列的索引 */
    while(front < rear) {
        int u = queue[front++];
        topOrder[topIndex++] = u; /* 记录拓扑序列 */

        AdjListNode* curr = graph->array[u].head;
        while(curr) {
            int v = curr->dest;
            int w = curr->weight;

            /* EC[v] = max(EC[v], EC[u] + weight) */
            if(EC[u] + w > EC[v]) {
                EC[v] = EC[u] + w;
            }
            inDegree[v]--;
            if(inDegree[v] == 0) {
                queue[rear++] = v;
            }
            curr = curr->next;
        }
    }
    
    /* 检查是否存在环 (如果不等于 V，说明有死循环，无法做工程排期) */
    if (topIndex != V) {
        printf("错误: AOE 网中存在环（逻辑死锁），无法计算关键路径！\n");
        free(inDegree); free(EC); free(LC); free(topOrder); free(queue);
        return;
    }

    /* ==========================================
     * 第二阶段：后向传递 (Backward Pass) 算 LC
     * ========================================== */
    int projectDuration = 0;
    for(int i = 1; i <= V; i++) {
        if(EC[i] > projectDuration) {
            projectDuration = EC[i];
        }
    }

    /* 初始化 LC 为项目的最终完成时间 */
    for (int i = 1; i <= V; i++) {
        LC[i] = projectDuration;
    }

    /* 逆拓扑顺序倒推：LC[u] = min(LC[u], LC[v] - weight) */
    for(int i = V -1; i >= 0; i--) {
        int u = topOrder[i];

        AdjListNode* curr = graph->array[u].head;
        while(curr) {
            int v = curr->dest;
            int w = curr->weight;
            if(LC[v] - w < LC[u]){
                LC[u] = LC[v] - w;
            }
            curr = curr->next;
        }
    }

    /* ==========================================
     * 第三阶段：计算 Slack，输出结果
     * ========================================== */
    printf("========== 关键路径分析 (CPM) ==========\n");
    printf("项目总最短耗时: %d\n\n", projectDuration);
    
    printf("顶点\tEC(最早)\tLC(最晚)\n");
    for (int i = 1; i <= V; i++) {
        printf("V%d\t%d\t\t%d\n", i, EC[i], LC[i]);
    }

    printf("\n【关键活动 (Critical Activities)】:\n");
    for (int u = 1; u <= V; u++) {
        AdjListNode* curr = graph->array[u].head;
        while (curr) {
            int v = curr->dest;
            int weight = curr->weight;
            
            /* 活动的机动时间 Slack = LC[终点] - EC[起点] - 耗时 */
            int slack = LC[v] - EC[u] - weight;
            
            if (slack == 0) {
                printf(" -> 活动 (V%d -> V%d) [耗时: %d]\n", u, v, weight);
            }
            curr = curr->next;
        }
    }
    printf("========================================\n");

    /* 释放内存 */
    free(inDegree); free(EC); free(LC); free(topOrder); free(queue);
}

/* ==========================================
 * 测试主函数
 * ========================================== */
int main() {
    int V = 9; 
    Graph* graph = CreateGraph(V + 1);

    /* 构造一个 AOE 网 (有向无环图)，注意这里使用的是单向边！
     * 请确保你的底层含有 AddDirectedEdge 函数 */
    AddDirectedEdge(graph, 1, 2, 6);
    AddDirectedEdge(graph, 1, 3, 4);
    AddDirectedEdge(graph, 1, 4, 5);
    AddDirectedEdge(graph, 2, 5, 1);
    AddDirectedEdge(graph, 3, 5, 1);
    AddDirectedEdge(graph, 4, 6, 2);
    AddDirectedEdge(graph, 5, 7, 9);
    AddDirectedEdge(graph, 5, 8, 7);
    AddDirectedEdge(graph, 6, 8, 4);
    AddDirectedEdge(graph, 7, 9, 2);
    AddDirectedEdge(graph, 8, 9, 4);

    CriticalPathMethod(graph);

    DestroyGraph(graph);
    return 0;
}