#include <stdio.h>
#include <stdlib.h>

/* ==========================================
 * 希尔排序核心函数
 * ========================================== */
void ShellSort(int* arr, int n){
    /* 外层循环：控制增量 gap，每次减半，直到 gap 为 1 */
    for(int gap = n / 2; gap > 0; gap /= 2) {
        /* 中层和内层循环：其实就是一个步长为 gap 的插入排序 */
        for(int i = gap; i < n; i++) {
           int temp = arr[i];
           int j;
           
           /* 向前找位置，只要前面的数比 temp 大，就把前面的数往后挪 gap 步 */
           for(j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
           }
           arr[j] = temp;   /* 将 temp 插入到正确位置 */
        }
    }
}

// void ShellSort(int* arr, int n){
//     for(int gap = n/2; gap > 0; gap /= 2){
//         for(int i = gap; i < n; i++){
//             int tmp = arr[i];
//             int j = i;
//             while(j > gap && arr[j-gap] > tmp){
//                 arr[j] = arr[j-gap];
//                 j -= gap;
//             }
//             arr[j] = tmp;
//         }
//     }
// }



/********************
 * 测试主函数
 ********************/
int main() {
    int arr[] = {12, 34, 54, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("原始数组: \n");
    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    ShellSort(arr, n);

    printf("排序后数组: \n");
    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}