#include "binary heap.h"
#include <stdio.h> 

int main(void) {
    BinaryHeap* heap = binary_heap_create();
    int values[] = {5, 3, 8, 1, 9, 2};
    for (size_t i = 0; i < sizeof(values)/sizeof(values[0]); i++) {
        binary_heap_insert(heap, values[i]);
    }

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