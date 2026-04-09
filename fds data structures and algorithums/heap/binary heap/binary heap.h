#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 堆结构体（不透明指针，隐藏实现细节） */
typedef struct BinaryHeap BinaryHeap;

/**
 * 创建一个新的空二叉堆（最小堆），默认初始容量为 16。
 * 返回堆指针，失败返回 NULL。
 */
BinaryHeap* binary_heap_create(void);

/**
 * 创建具有指定初始容量的空二叉堆。
 * 返回堆指针，失败返回 NULL。
 */
BinaryHeap* binary_heap_create_with_capacity(size_t capacity);

/**
 * 销毁堆，释放所有内存。
 */
void binary_heap_destroy(BinaryHeap* heap);

/**
 * 向堆中插入一个整数。成功返回 0，失败返回 -1。
 */
int binary_heap_insert(BinaryHeap* heap, int value);

/**
 * 取出并删除堆中的最小元素（根节点）。
 * 若堆非空，将最小值写入 out_value 并返回 0；
 * 若堆为空，返回 -1，out_value 保持不变。
 */
int binary_heap_extract_min(BinaryHeap* heap, int* out_value);

/**
 * 查看堆中的最小元素而不删除。
 * 若堆非空，将最小值写入 out_value 并返回 0；
 * 若堆为空，返回 -1，out_value 保持不变。
 */
int binary_heap_peek_min(const BinaryHeap* heap, int* out_value);

/**
 * 判断堆是否为空。
 */
bool binary_heap_is_empty(const BinaryHeap* heap);

/**
 * 返回堆中当前元素个数。
 */
size_t binary_heap_size(const BinaryHeap* heap);

/**
 * 清空堆中的所有元素，但保留内部数组容量。
 */
void binary_heap_clear(BinaryHeap* heap);

#ifdef __cplusplus
}
#endif

#endif /* BINARY_HEAP_H */
