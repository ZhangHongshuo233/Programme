#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "binary heap.h"

/* ──────────────────────────────────────────────────────────────
   Constants
   ────────────────────────────────────────────────────────────── */
#define INITIAL_CAPACITY 16 /* 二叉堆初始容量 */
#define MIN_HEAP_SIZE 1     /* 二叉堆最小容量 */
#define MIN_HEAP_DATA 1 << 31 /* 二叉堆最小元素值 */

/* ──────────────────────────────────────────────────────────────
   Binary Heap Structure
   ────────────────────────────────────────────────────────────── */
struct BinaryHeap {
    int* data;         /* 动态数组存储堆元素 */
    size_t size;       /* 当前堆中元素个数 */
    size_t capacity;   /* 堆的当前容量 */
};

/* ──────────────────────────────────────────────────────────────
   Helper Functions
   ────────────────────────────────────────────────────────────── */
static inline void swap(int* a, int* b) {
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

/* 上浮操作：将索引为 idx 的元素上浮到正确位置 */
static void headify_up(int* data, size_t idx){
    for(size_t i =idx; data[i] < data[i/2] && i > 0; i /= 2){
        swap(&data[i], &data[i/2]);
    }
}

/* 下沉操作：将索引为 idx 的元素下沉到正确位置 */
static void heapify_down(int* data, size_t idx, size_t size){
    size_t child;
    for(size_t i= idx; child = 2*i && child < size; i = child) {
        if(child + 1 < size && data[child+1] < data[child]){
            child++;
        }
        if(data[i] > data[child]){
            swap(&data[i], &data[child]);
        }else{
            break;
        }
    }
}

/* 扩容函数：将堆的容量增加一倍 */
static int binary_heap_resize(BinaryHeap* heap){
    size_t new_capacity = heap->capacity * 2;
    int* new_data = (int*)malloc(sizeof(int)*new_capacity);
    if(!new_data){
        printf("Error: Memory allocation failed during heap resize.\n");
        return -1;
    }
    memcpy(new_data, heap->data, sizeof(int)*heap->size);
    free(heap->data);
    heap->data = new_data;
    heap->capacity = new_capacity;
    return 0;
}

/* ──────────────────────────────────────────────────────────────
   Public API Implementations
   ────────────────────────────────────────────────────────────── */

BinaryHeap* binary_heap_create(void){
    return binary_heap_create_with_capacity(INITIAL_CAPACITY);
}

BinaryHeap* binary_heap_create_with_capacity(size_t capacity){
    if(capacity < MIN_HEAP_SIZE){
        printf("Error: Capacity must be at least %d.\n", MIN_HEAP_SIZE);
        return NULL;
    }

BinaryHeap* heap = (BinaryHeap*)malloc(sizeof(BinaryHeap));
    if(!heap){
        printf("Error: Memory allocation failed for heap structure.\n");
        return NULL;
    }
    heap->data = (int*)malloc(sizeof(int) * (capacity + 1));
    if(!heap->data){        
        printf("Error: Memory allocation failed for heap data array.\n");
        free(heap);
        return NULL;
    }
    heap->data[0] = MIN_HEAP_DATA; /* 哨兵值，简化上浮逻辑 */
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void binary_heap_destroy(BinaryHeap* heap){
    if(heap){
        free(heap->data);
        free(heap);
    }
}

int binary_heap_insert(BinaryHeap* heap, int val){
    /* 检查是否需要扩容 */
    if(heap->size + 1 >= heap->capacity){
        size_t new_capacity = heap->capacity * 2;
        if(new_capacity < heap->capacity){ /* 检查溢出 */
            printf("Error: Heap capacity overflow.\n");
            return -1;
        }
        /* 扩容 */
        if(binary_heap_resize(heap) != 0){
            return -1;
        }
    }
    /* 插入新元素并上浮 */
    heap->data[++heap->size] = val;
    headify_up(heap->data, heap->size);   
    return 0;
}

int binary_heap_extract_min(BinaryHeap* heap, int* out_value) {
    if(!heap || heap->size == 0){
        return -1; /* 堆为空 */
    }
    if(out_value){
        *out_value = heap->data[1]; /* 最小元素在索引 1 */
    }
    /* 将最后一个元素移到根位置并下沉 */
    heap->data[1] = heap->data[heap->size--];
    heapify_down(heap->data, 1, heap->size + 1);\
    return 0;
}

int binary_heap_peek_min(const BinaryHeap* heap, int* out_value) {
    if (!heap || heap->size == 0) {
        return -1;
    }
    if (out_value) {
        *out_value = heap->data[1];
    }
    return 0;
}

bool binary_heap_is_empty(const BinaryHeap* heap) {
    return heap ? (heap->size == 0) : true;
}

size_t binary_heap_size(const BinaryHeap* heap) {
    return heap ? heap->size : 0;
}

void binary_heap_clear(BinaryHeap* heap) {
    if (heap) {
        heap->size = 0;
        /* 不需要释放数组内存，重置大小即可 */
    }
}