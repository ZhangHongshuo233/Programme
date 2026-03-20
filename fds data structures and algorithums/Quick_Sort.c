#include <stdio.h>

// 交换两个元素的值
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

/*
 * 分区函数 (Partition)
 * arr: 待排序数组
 * low: 起始索引
 * high: 结束索引
 * 返回值: 基准元素排序后的正确索引位置
 */
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // 选择最后一个元素作为基准
    int i = (low - 1);     // i 是较小元素的索引

    for (int j = low; j <= high - 1; j++) {
        // 如果当前元素小于或等于基准
        if (arr[j] <= pivot) {
            i++; // 移动较小元素的索引
            swap(&arr[i], &arr[j]);
        }
    }
    // 把基准元素放到正确的位置 (i + 1)
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/*
 * 快速排序主函数
 * arr: 待排序数组
 * low: 起始索引
 * high: 结束索引
 */
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // pi 是分区索引，arr[pi] 已经在正确的位置
        int pi = partition(arr, low, high);

        // 递归排序基准左边的子数组
        quickSort(arr, low, pi - 1);
        
        // 递归排序基准右边的子数组
        quickSort(arr, pi + 1, high);
    }
}

// 打印数组
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);   
    printf("%d",n);
    
    printf("原始数组: \n");
    printArray(arr, n);
    
    quickSort(arr, 0, n - 1);
    
    printf("排序后的数组: \n");
    printArray(arr, n);
    return 0;
}
