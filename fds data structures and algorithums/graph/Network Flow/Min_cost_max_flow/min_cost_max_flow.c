#include <stdio.h>
#include <stdbool.h>

#define MAX_V 100
#define INF 1000000000

/* * 全局变量结构模拟 (为了保持签名简洁)
 * 现实工程中最好封装进 struct Graph
 */
int capacity[MAX_V][MAX_V];
int cost[MAX_V][MAX_V];      /* 单位流量的成本 */
int flow[MAX_V][MAX_V];      /* 当前已占用的流量 */

/* 使用 SPFA 寻找最小费用的增广路径 */
bool spfa(int V, int s, int t, int parent[], int *path_flow, int *path_cost) {
    int dist[MAX_V];         /* 记录最小总费用 */
    bool in_queue[MAX_V];
    int queue[MAX_V * 10];   /* 循环队列 */
    int front = 0, rear = 0;

    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        in_queue[i] = false;
        parent[i] = -1;
    }

    dist[s] = 0;
    queue[rear++] = s;
    in_queue[s] = true;

    /* 记录到达每个节点的路径最小瓶颈 */
    int min_cap[MAX_V];
    min_cap[s] = INF;

    while (front < rear) {
        int u = queue[front++];
        in_queue[u] = false;

        for (int v = 0; v < V; v++) {
            /* 残量 = 容量 - 已经流过的量 */
            int residual_cap = capacity[u][v] - flow[u][v];
            
            /* 如果还能通水，且借道 u 过去费用更低！ */
            if (residual_cap > 0 && dist[u] + cost[u][v] < dist[v]) {
                dist[v] = dist[u] + cost[u][v];
                parent[v] = u;
                min_cap[v] = (min_cap[u] < residual_cap) ? min_cap[u] : residual_cap;

                if (!in_queue[v]) {
                    queue[rear++] = v;
                    in_queue[v] = true;
                }
            }
        }
    }

    if (dist[t] == INF) return false; /* 找不到路了 */

    *path_flow = min_cap[t];
    *path_cost = dist[t];
    return true;
}

/* 最小费用最大流算法 (MCMF) */
void MinCostMaxFlow(int V, int s, int t) {
    int max_flow = 0;
    int min_cost = 0;
    int parent[MAX_V];
    int path_flow, path_cost;

    /* 只要还能找到最便宜的路径，就压榨它！ */
    while (spfa(V, s, t, parent, &path_flow, &path_cost)) {
        /* 更新流量和反向边代价 */
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            flow[u][v] += path_flow;     /* 正向增加流量 */
            flow[v][u] -= path_flow;     /* 允许反悔 */
        }
        max_flow += path_flow;
        min_cost += path_flow * path_cost; /* 总费用 = 流量 * 路径单价 */
    }

    printf(">>> MCMF 结算:\n");
    printf("最大流量 (Max Flow): %d\n", max_flow);
    printf("最小总费用 (Min Cost): %d\n", min_cost);
}