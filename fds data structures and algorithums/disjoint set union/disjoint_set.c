#include "disjoint_set.h"
#include <stdlib.h>
#include <stdio.h>

DisjointSet* CreateDisjointSet(int size) {
    DisjointSet* ds = (DisjointSet*)malloc(sizeof(DisjointSet));
    ds->parent = (int*)malloc(sizeof(int) * (size + 1)); 
    ds->size = size;
    // 初始化：每个元素自己是一个集合，是根节点。
    // 我们用负数表示根节点，其绝对值表示集合的大小（初始大小为1，所以是 -1）
    for(int i = 0; i <= size; i++) {
        ds->parent[i] = -1;
    }
    return ds;
}

// 核心操作 1：查找 (Find) + 路径压缩 (Path Compression)
int Find(DisjointSet* ds, int x){
    //如果 S[X] <= 0，说明找到了根节点
    if(ds->parent[x] < 0) {
        return x;
    }else {
        //// 路径压缩：在回溯时，将路径上的所有节点直接连到根节点上
        return ds->parent[x] = Find(ds, ds->parent[x]);
    }
}

//路径压缩：在回溯时，将路径上的所有节点直接连到根节点上
int Find_iteration(DisjointSet* ds, int x){
    int root = x;
    while(ds->parent[root] >= 0) {
        root = ds->parent[root];
    }
    // Path Compression
    int trail = x, lead;
    while(trail != root){
        lead = ds->parent[trail];
        ds->parent[trail] = root;
        trail =lead;
    }
    return root;
}

// 核心操作 2：合并 (Union) + 按大小合并 (Smart Union)
void Union(DisjointSet* ds, int root1, int root2){
    int r1 = Find(ds, root1);
    int r2 = Find(ds, root2);

    if(r1 == r2) {
        return; // 已经在同一个集合中
    }

    // 按大小合并：将较小的集合合并到较大的集合上
    // 注意：因为根节点存的是负的大小，所以数值越小，代表集合越大
    if(ds->parent[r2] < ds->parent[r1]) {
        // r2 的集合更大，r1 合并到 r2 上
        ds->parent[r2] += ds->parent[r1];
        ds->parent[r1] = r2;
    }
    else {
        // r1 的集合更大，r2 合并到 r1 上
        ds->parent[r1] += ds->parent[r2];
        ds->parent[r2] = r1;
    }
}
  
void DestroyDisjointSet(DisjointSet* ds) {
    if(ds == NULL) {
        return;
    }
    if(ds->parent != NULL) {
        free(ds->parent);
    }
    free(ds);
}