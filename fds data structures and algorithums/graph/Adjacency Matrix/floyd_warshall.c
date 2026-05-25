/*
 * Floyd-Warshall 算法实现(多源最短路径)
    * 适用于有向图和无向图，支持负权边但不支持负权环
    * 时间复杂度 O(V^3)，空间复杂度 O(V^2)
    * 主要思想：动态规划，逐步允许更多的中间节点，更新最短路径'
    * 路径重建：通过维护一个前驱矩阵 (path)，可以在算法结束后重建最短路径
    
    * 示例图：
        0 --3--> 1
        |        |
        8        2
        |        |
        v        v
        2 <--1-- 3
        * 初始邻接矩阵 (INF 代表无直接连接)：
        0   3   INF 7
        8   0   2   INF
        5   INF 0   1
        2   INF INF 0
        * 最终输出：
        最短距离矩阵 (Dist):
        0   3   5   6
        8   0   2   3
        5   8   0   1
        2   5   7   0
        前驱节点矩阵 (Path):
        -   0   0   2
        1   -   1   2
        3   -   -   2
        0   -   -   -
 */


#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000 /* 防止相加溢出 */

/* * 打印最终的距离矩阵和路径矩阵
 */
void PrintMatrix(int V, int dist[][V], int path[][V]) {
    printf("========== 最短距离矩阵 (Dist) ==========\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF) printf("INF\t");
            else printf("%d\t", dist[i][j]);
        }
        printf("\n");
    }

    printf("\n========== 前驱节点矩阵 (Path) ==========\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (path[i][j] == -1) printf("-\t");
            else printf("%d\t", path[i][j]);
        }
        printf("\n");
    }
    printf("=========================================\n\n");
}

/* * Floyd-Warshall 算法核心
 * 传入顶点数 V 和初始的邻接矩阵 graph
 */
void FloydWarshall(int V, int graph[][V]) {
    /* 创建距离矩阵和路径(前驱)矩阵 */
    int dist[V][V];
    int path[V][V];

    /* 1. 初始化矩阵 */
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];
            /* 如果 i 到 j 有直接边，前驱就是 i；否则没有前驱 (-1) */
            if (graph[i][j] != INF && i != j) {
                path[i][j] = i; 
            } else {
                path[i][j] = -1;
            }
        }
    }

    /* 2. Floyd-Warshall 算法核心  */
    for (int k = 0; k < V; k++) {          /* k 作为允许借道的中间节点 */
        for (int i = 0; i < V; i++) {      /* i 作为起点 */
            for (int j = 0; j < V; j++) {  /* j 作为终点 */
                
                /* 如果借道 k 能让 i 到 j 的距离变短：
                 * 也就是 dist[i][k] + dist[k][j] < dist[i][j] */
                if (dist[i][k] != INF && dist[k][j] != INF && 
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    
                    dist[i][j] = dist[i][k] + dist[k][j];
                    /* 更新路径：既然 i 到 j 最后一步是顺着 k 到 j 的路过来的，
                     * 那 i 到 j 的前驱就等于 k 到 j 的前驱 */
                    path[i][j] = path[k][j];
                }
            }
        }
    }

    /* 3. 输出结果 */
    PrintMatrix(V, dist, path);
}

/* * 测试主函数
 */
int main() {
    int V = 4;
    /* 构造初始邻接矩阵 (0 代表自己到自己，INF 代表无直接连接) */
    int graph[4][4] = {
        {0,   3,   INF, 7},
        {8,   0,   2,   INF},
        {5,   INF, 0,   1},
        {2,   INF, INF, 0}
    };

    printf("开始执行 Floyd-Warshall 算法...\n\n");
    FloydWarshall(V, graph);

    return 0;
}