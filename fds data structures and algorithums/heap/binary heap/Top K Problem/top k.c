/*
 * Top K Problem
    * Given an array of integers and an integer k, find the k largest elements in the array.
    * Example:
        Input: arr = [3, 1, 5, 12, 2, 11], k = 3
        Output: [5, 12, 11] 
 */

#include <stdio.h>
#include <stdlib.h>
/*Method 1: Quicksort
 * time complexity: O(n log n) on average, O(n^2) in the worst case
 * space complexity: O(log n) on average, O(n) in the worst case
*/
int compare(const void* a, const void* b) {
    return (*(int*)b - *(int*)a); // 降序排序
}

void top_k(int* arr, size_t n, int k) {
    if (k <= 0 || k > n) {
        printf("Invalid value of k.\n");
        return;
    }
    qsort(arr, n, sizeof(int), compare); // 对数组进行排序
    printf("Top %d elements: ", k);
    for (int i = 0; i < k; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/*
 * Method 2: Min-Heap
 * time complexity: O(n log k)
 * space complexity: O(k)
 */

/* ─────────────────────────────────────────────────────────────
    Min-Heapify Function
   ────────────────────────────────────────────────────────────── */
void min_heapify_down(int* arr, int idx, int size) {
    int child;
    for(int i = idx; (child = 2 * i + 1) < size; i = child){
        if(child + 1 < size && arr[child + 1] < arr[child]){
            child++;
        }
        if(arr[i] > arr[child]){
            arr[i] ^= arr[child];
            arr[child] ^= arr[i];
            arr[i] ^= arr[child];
        }
        else break;
    }
}

void min_heapify_up(int* arr, int idx){
    for(int i = idx; arr[i] < arr[(i-1)/2] && i > 0; i = (i-1)/2){
        arr[i] ^= arr[(i-1)/2];
        arr[(i-1)/2] ^= arr[i];
        arr[i] ^= arr[(i-1)/2];
    }
}

/* ─────────────────────────────────────────────────────────────
    Min-Heap Based Top K Function
   ────────────────────────────────────────────────────────────── */
void top_k_largest(int* arr, int n, int k, int* result) {
    if(k <= 0 || n <= 0) return;

    if(k >= n) {
        for(int i = 0; i < n; i++){
            result[i] = arr[i];
        }
        return;
    }

    /*construct min-heap*/
    int* heap = (int*)malloc(sizeof(int)*k);
    if(!heap){
        printf("Error: Memory allocation failed for heap.\n");
        return;
    }
    for(int i = 0; i < k; i++){
        heap[i] =arr[i];
        min_heapify_up(heap, i);
    } 
    /*traverse the remaining elements*/
    for(int i = k; i < n; i++){
        if(arr[i] > heap[0]){
            heap[0] = arr[i];
            min_heapify_down(heap, 0, k);
        }
    }
    /*copy the elements from the heap to the result array*/
    for(int i = 0; i < k; i++){
        result[i] = heap[i];
    }
    free(heap);


}