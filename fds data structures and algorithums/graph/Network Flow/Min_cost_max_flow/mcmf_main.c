#include <stdio.h>
#define MAX_V 100
extern void MinCostMaxFlow(int V, int s, int t);
extern int capacity[MAX_V][MAX_V];
extern int cost[MAX_V][MAX_V];

int main(){
    int V = 4;
    /* 初始化示例网络 */
    for(int i=0;i<V;i++) for(int j=0;j<V;j++){ capacity[i][j]=0; cost[i][j]=0; }
    capacity[0][1]=3; cost[0][1]=1;
    capacity[0][2]=2; cost[0][2]=2;
    capacity[1][3]=2; cost[1][3]=3;
    capacity[2][3]=3; cost[2][3]=1;

    MinCostMaxFlow(V, 0, 3);
    return 0;
}
