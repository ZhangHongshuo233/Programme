#include <stdio.h>
#include <stdlib.h>

void swap(int* a,int* b){
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}
void max_heap_sift_down(int* arr, int idx, int heap_size) {
    int child;
    for(int i = idx; (child = 2 * i + 1) < heap_size; i = child){
        if(child + 1 < heap_size && arr[child] < arr[child + 1]){
            child++;
        }
        if(arr[i] < arr[child]){
            swap(&arr[i], &arr[child]);
        }
        else{
            break;
        }
    }
}

void heap_sort(int* arr ,int n){
    /* Build max heap:
        *as for 0-based indexing, the parent of a node at index i is at index (i-1)/2,
        * The last non-leaf node is at index ((n-1)-1)/2 = n/2 - 1,we use linear algorithm to build the heap.
        * if it is 1-based indexing, the parent of a node at index i is at index i/2,
        * The last non-leaf node is at index n/2.
     */
    for(int i = n/2 -1; i >= 0; i--){
        max_heap_sift_down(arr, i, n);
    }
    /* Heap sort */
    for(int i = n - 1; i > 0; i--){
        swap(&arr[0], &arr[i]);
        max_heap_sift_down(arr, 0, i);
    }
}