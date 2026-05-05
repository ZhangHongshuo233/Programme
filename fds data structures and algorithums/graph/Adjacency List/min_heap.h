#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <stdio.h>
#include <stdlib.h>

/* 堆节点：存储顶点索引和它当前的距离 */
typedef struct {
    int vertex;
    int dist;
} HeapNode;

/* 最小堆主体结构 */
typedef struct {
    HeapNode* array;    /* 存储节点的动态数组 */
    int size;           /* 当前堆中的元素个数 */
    int capacity;       /* 堆的最大容量 */
} MinHeap;

/* API 接口 */
MinHeap* CreateMinHeap(int capacity);
void Push(MinHeap* heap, int vertex, int dist);
HeapNode Pop(MinHeap* heap);
int IsEmpty(MinHeap* heap);
void DestroyMinHeap(MinHeap* heap);

#endif // MIN_HEAP_H