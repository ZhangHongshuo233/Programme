#include "min_heap.h"

/* 内部辅助函数：交换两个堆节点 */
static void SwapNode(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

MinHeap* CreateMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    if(!heap) return NULL;
    
    heap->capacity = capacity;
    heap->size = 0;
    heap->array = (HeapNode*)malloc(capacity * sizeof(HeapNode));
    
    if(!heap->array) {
        free(heap);
        return NULL;
    }
    return heap;
}

/* 入队并保持最小堆性质 (时间复杂度 O(log N)) */
void Push(MinHeap* heap, int vertex, int dist) {
    if (!heap || heap->size >= heap->capacity) return;

    /* 先将新元素放到数组最后 */
    int i = heap->size++;
    heap->array[i].vertex = vertex;
    heap->array[i].dist = dist;

    /* 向上调整 (上浮)：如果比父节点小，就交换位置 */
    while (i != 0 && heap->array[i].dist < heap->array[(i - 1) / 2].dist) {
        SwapNode(&heap->array[i], &heap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

/* 弹出最小元素并保持最小堆性质 (时间复杂度 O(log N)) */
HeapNode Pop(MinHeap* heap) {
    HeapNode emptyNode = {-1, -1};
    if (!heap || heap->size == 0) return emptyNode;

    if (heap->size == 1) {
        heap->size--;
        return heap->array[0];
    }

    /* 取出根节点(最小值) */
    HeapNode root = heap->array[0];
    
    /* 将最后一个节点移到根部 */
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;

    /* 向下调整 (下沉) */
    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < heap->size && heap->array[left].dist < heap->array[smallest].dist) {
            smallest = left;
        }
        if (right < heap->size && heap->array[right].dist < heap->array[smallest].dist) {
            smallest = right;
        }

        if (smallest != i) {
            SwapNode(&heap->array[i], &heap->array[smallest]);
            i = smallest;
        } else {
            break; /* 已经满足最小堆性质，退出循环 */
        }
    }
    return root;
}

int IsEmpty(MinHeap* heap) {
    return !heap || heap->size == 0;
}

void DestroyMinHeap(MinHeap* heap) {
    if (!heap) return;
    free(heap->array);
    free(heap);
}