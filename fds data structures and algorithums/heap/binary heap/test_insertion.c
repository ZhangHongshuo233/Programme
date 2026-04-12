#include "binary heap.h"
#include <stdio.h> 

int main(void) {
    BinaryHeap* heap = binary_heap_create();
    int values[] = {5, 3, 8, 1, 9, 2};
    /*使用逐个建堆法：
     * 插入元素后，堆会自动调整以保持最小堆性质
     */
    heap_build_insertion(heap, values, sizeof(values)/sizeof(values[0]));
    
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