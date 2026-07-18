#include <stdio.h>

#define MAX_NODES 100 // 为安全起见，通常线段树数组开到原数组大小的 4 倍

int tree[MAX_NODES]; // 线段树数组
int arr[] = {7, 2, 5, 8, 3}; 

/* 1. 构建线段树 */
void Build(int node, int start, int end) {
    if(start ==  end) {
        tree[node] = arr[node];
    }

    int mid = start + (end - start) / 2;
    Build(2 * node, start, mid);
    Build(2 * node + 1, mid + 1, end);

    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

/* 2. 区间查询 */
Query(int node, int start, int end, int L, int R) {
    if(R < start || L > end){
        return 0;
    }

    if(L <= start && end <= R){
        return tree[node];
    }

    int mid = start + (end - start) / 2;

    Query()
}