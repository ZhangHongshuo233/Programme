#include <stdio.h>
#include <stdlib.h>

/* ==========================================
 * 合并两个有序子数组 (治)
 * ========================================== */
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
 * 递归拆分数组 (分)
 * ========================================== */
void MSort(int arr[], int temp[], int left, int right) {
    if(left < right) {
        int mid = left + (right - left) / 2;

        /* 递归拆分左半边 */
        MSort(arr, temp, left, mid);
        /* 递归拆分右半边 */
        MSort(arr, temp, mid + 1, right);

        /* 合并两个有序子数组 */
        Merge(arr, temp, left, mid, right);
    }
}

/* ==========================================
 * 归并排序主入口 (负责开辟临时空间)
 * ========================================== */
void MergeSort(int arr[], int n) {
    /* 归并排序的核心代价：需要 O(N) 的辅助空间 */
    int* temp = (int*)malloc(n * sizeof(int));
    if (temp != NULL) {
        MSort(arr, temp, 0, n - 1);
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
    int arr[] = {38, 27, 43, 3, 9, 82, 10, 19};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf(">>> 归并排序 (Merge Sort) 演示 <<<\n");
    printf("排序前: ");
    PrintArray(arr, n);

    MergeSort(arr, n);

    printf("排序后: ");
    PrintArray(arr, n);

    return 0;
}