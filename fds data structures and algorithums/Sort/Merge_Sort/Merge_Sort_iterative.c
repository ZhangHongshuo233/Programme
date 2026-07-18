#include <stdio.h>
#include <stdlib.h>

void Merge(int arr[], int temp[], int left, int mid, int right) {
    int i = left;      /* 左半边数组的指针 */
    int j = mid + 1;   /* 右半边数组的指针 */
    int k = left;      /* 临时数组 temp 的指针 */

    /* 将两个有序子数组合并到临时数组 temp 中 */
    while(i <= mid && j <= right) {
        if(arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        }else {
            temp[k++] = arr[j++];
        }
    }

    /* 如果左边还有剩余，全部直接追加到 temp 尾部 */
    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    /* 如果右边还有剩余，全部直接追加到 temp 尾部 */
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    /* 将排好序的 temp 数组拷贝回原数组 arr */
    for (int p = left; p <= right; p++) {
        arr[p] = temp[p];
    }
}


/* ==========================================
 * 自底向上的迭代循环归并 (非递归核心)
 * ========================================== */
void MergeSortIterativeLoop(int arr[], int temp[], int n) {
    /* step 为子区间步长，从 1 开始每次翻倍增长 */
    for(int step = 1; step < n; step *= 2){
        for(int i = 0; i < n; i += 2 * step){
            int left = i;
            int mid = i + step - 1;
            int right = i + step * 2 -1;

            /* 如果右半部分的起点 (mid + 1) 已经出界，说明落单了，无需合并 */
            if(mid + 1 >= n){
                continue;
            }

            /* 如果右半部分的终点超出数组最大索引，强行截断到 N - 1 */
            if(right >= n ){
                right = n - 1;
            }

            /* 合并这两个相邻的子区间 */
            Merge(arr,temp,left,mid,right);
        }
    }
}

/* ==========================================
 * 归并排序迭代版入口 (负责开辟临时空间)
 * ========================================== */
void MergeSortIterative(int arr[], int n) {
    /* 归并排序的核心代价：需要 O(N) 的辅助空间 */
    int* temp = (int*)malloc(n * sizeof(int));
    if (temp != NULL) {
        MergeSortIterativeLoop(arr, temp, n);
        free(temp); 
    } else {
        printf("内存分配失败！\n");
    }
}

/* 打印数组辅助函数 */
void PrintArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    /* 采用你经典的测试数据集 */
    int arr[] = {38, 27, 43, 3, 9, 82, 10, 19};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf(">>> 迭代归并排序 (Iterative Merge Sort) 演示 <<<\n");
    printf("排序前: ");
    PrintArray(arr, n);

    MergeSortIterative(arr, n);

    printf("排序后: ");
    PrintArray(arr, n);

    return 0;
}
