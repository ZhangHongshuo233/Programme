#include "binary heap.h"
#include <stdio.h> 

int main(void) {
    BinaryHeap* heap = binary_heap_create();
    int values[] = {5, 3, 8, 1, 9, 2};
    /*使用线性建堆法：
     * 先将所有元素插入到堆中，然后一次性调整堆以满足最小堆性质
     */
    heap_build_linear(heap, values, sizeof(values)/sizeof(values[0]));
    printf("Heap size: %zu\n", binary_heap_size(heap));

    int min_val;
    while (!binary_heap_is_empty(heap)) {
        binary_heap_extract_min(heap, &min_val);
        printf("%d ", min_val);
    }
    printf("\n");
 
    binary_heap_destroy(heap);
    return 0;
}