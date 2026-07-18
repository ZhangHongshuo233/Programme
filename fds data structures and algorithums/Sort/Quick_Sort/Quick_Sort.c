#include <stdio.h>
#include <stdlib.h>

#define CUTOFF 10 // PPT 第 4 页要求的截断阈值

// 基础原地交换函数
void Swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp; 
}

// 基础插入排序（用于小数组截断优化）
void InsertionSort(int A[], int N) {
    for (int p = 1; p < N; p++) {
        int temp = A[p];
        int i;
        for (i = p; i > 0 && A[i - 1] > temp; i--) {
            A[i] = A[i - 1];
        }
        A[i] = temp;
    }
}

// 1. 三数取中法选择主元 (PPT 第 2 页)
int Median3(int A[], int Left, int Right) {
    int Center = Left + (Right - Left) / 2;
    
    // 对左、中、右三数进行排序
    if (A[Left] > A[Center]) Swap(&A[Left], &A[Center]);
    if (A[Left] > A[Right])  Swap(&A[Left], &A[Right]);
    if (A[Center] > A[Right]) Swap(&A[Center], &A[Right]);
    
    // 将主元 Pivot 隐藏到倒数第二个位置 (Right - 1)
    Swap(&A[Center], &A[Right - 1]);
    return A[Right - 1]; // 返回主元
}

// 快速排序核心递归体
void QSort(int A[], int Left, int Right) {
    // 2. 数组大小大于阈值时使用快排，否则使用插入排序 (PPT 第 4 页)
    if (Left + CUTOFF <= Right) {
        int Pivot = Median3(A, Left, Right);
        int i = Left;
        int j = Right - 1;
        
        // 3. 划分策略 (Partitioning Strategy)
        for ( ; ; ) {
            // i 向右扫描，直到遇到大于等于 Pivot 的数（PPT 核心讨论：等于时同样停止交换）
            while (A[++i] < Pivot) {}
            // j 向左扫描，直到遇到小于等于 Pivot 的数
            while (A[--j] > Pivot) {}
            
            if (i < j) {
                Swap(&A[i], &A[j]); // 满足条件，原地对调
            } else {
                break;
            }
        }
        // 将主元从隐藏位 (Right - 1) 还原归位到中间分界点 i
        Swap(&A[i], &A[Right - 1]);
        
        // 递归治理左右两侧宇宙
        QSort(A, Left, i - 1);
        QSort(A, i + 1, Right);
    } else {
        InsertionSort(A + Left, Right - Left + 1);
    }
}

// 统一的外部调用接口
void QuickSort(int A[], int N) {
    QSort(A, 0, N - 1);
}

int main() {
    int arr[] = {13, 81, 92, 43, 65, 31, 57, 26, 75, 0}; // PPT 第一页标准样例数据
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Original array:\n");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
    
    QuickSort(arr, n);
    
    printf("\nSorted array (Optimized QuickSort):\n");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
    return 0;
}