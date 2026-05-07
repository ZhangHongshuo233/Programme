#include <stdio.h>
#include <stdlib.h>
#include "adj_list.h"

// 拓扑排序 (返回 1 表示成功，返回 0 表示图中有环)
int TopologicalSort(Graph* graph, int* result) {
    int V = graph->V;
    int* in_degree = (int*)calloc(V, sizeof(int));  // 入度数组，全初始化为 0

    // 第 1 步：统计所有顶点的入度
    for(int i = 0; i < V; i++) {
        AdjListNode* curr = graph->array[i].head;
        while(curr) {
            in_degree[curr->dest]++;
            curr = curr->next;
        }
    }

    // 第 2 步：初始化队列，将所有入度为 0 的顶点入队
    // 这里为了精简，我们用一个简单的数组模拟队列
    int* queue = (int*)malloc(V * sizeof(int));
    int front = 0, rear = 0;
    
    for(int i = 0; i < V; i++) {
        if(in_degree[i] == 0) {
            queue[rear++] = i;  // 入队
        }
    }

    // 第 3 步：抽丝剥茧
    int count = 0;  // 记录已处理的顶点数量
    while(front < rear) {   // 队列不为空
        int u = queue[front++];  // 出队
        result[count++] = u;     // 存入结果序列

        // 遍历顶点 u 的所有邻居
        AdjListNode* curr = graph->array[u].head;
        while(curr) {
            int v = curr->dest;
            in_degree[v]--;  // 斩断边，邻居的入度减 1

            // 如果邻居的入度变为 0，说明前置已全部满足，入队
            if(in_degree[v] == 0) {
                queue[rear++] = v;
            }
            curr = curr->next;
        }

        //释放内存
        free(in_degree); 
        free(queue);

        // 第 4 步:检查是否有环
        if(count == V) {
            return 1;  // 成功，返回 1
        } else {
            return 0;  // 图中有环，返回 0
        }
    }
}

// 判断给定的 seq 序列是否为合法的拓扑排序
// 返回 1 为合法，0 为非法
int IsTopSort(Graph* graph, int* seq) {
    int V = graph->V;
    int* position = (int*)malloc(V * sizeof(int));

    // 1. 记录每个顶点在 seq 中的位置
    for(int i = 0; i < V; i++) {
        position[seq[i]] = i;
    }

    // 2. 遍历图中的所有有向边
    for(int i = 0; i < V; i++) {
        AdjListNode* curr = graph->array[i].head;
        while(curr) {
            int u = i;
            int v = curr->dest;
            // 核心判定：如果起始点 u 的位置在目标点 v 的后面，则违背了拓扑排序
            if(position[u] > position[v]) {
                printf("检验失败！边 %d -> %d 发生冲突！\n", u, v);
                free(position);
                return 0;  
            }
            curr = curr->next;
        }
    }
    free(position);
    return 1;  // seq 是合法的拓扑排序
}