#include <stdio.h>
//本题要求编写程序，将给定的n个整数存入数组中，将数组中的这n个数逆序存放，再按顺序输出数组中的元素。

#define MAXN 10 
int main()
{
    int i, n, temp;
    int a[MAXN];
    //读入数组元素个数及元素值
    scanf("%d", &n);
    for(i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }

    // // 逆序数组(方法1):交换首尾元素(只需要遍历数组的前半部分)
    // for(i = 0; i < n / 2; i++){
    //     temp = a[i];
    //     a[i] = a[n - 1 - i];
    //     a[n - 1 - i] = temp;
    // }

    // //方法1的等价方法（递归形式）
    // void reverseArray(int arr[], int i, int n) {
    //     if (i >= n / 2) 
    //         return;
    //     int temp = arr[i];
    //     arr[i] = arr[n - 1 - i];
    //     arr[n - 1 - i] = temp;
    //     reverseArray(arr, i + 1);
    // }

    // //方法1的另一种等价方法(指针形式)
    // void reverseArray(int arr[], int*p, int*q) {
    //     if (p >= q) 
    //         return;
    //     int temp = *p;
    //     *p = *q;
    //     *q = temp;
    //     reverseArray(arr, p + 1, q - 1);
    // }
    // reverseArray(a, a, a + n - 1);
    // //或者不使用递归也可以
    // void reverseArrayIterative(int arr[], int n) {
    //     int* p =arr;
    //     int*q = arr+ n - 1；
    //     while(p<q){
    //         int temp = *p;
    //         *q=*p;
    //         *p =temp;
    //         p++;
    //         q--;
    //     }
    // }
    //reverseArray(arr,n);
    //也可以这样传参
    // void reverseArray(int*p,int*q){
    //     while(p<q){
    //         int temp=*p;
    //         *p=*q;
    //         *q=temp;
    //         p++;
    //         q--;
    //     }
    //}
    // reverseArray(arr,arr+n-1);
    // 逆序数组(方法2):构建临时数组
    int b[MAXN];
    for(i = 0; i < n; i++){
        b[i] = a[n - 1 - i];
    }
    for(i = 0; i < n; i++){
        a[i] = b[i];
    }



    
//    //逆序数组(方法3):递归
//     void reverseArray(int arr[], int start, int end) {
//     if (start < end) {
//         int temp = arr[start];
//         arr[start] = arr[end];
//         arr[end] = temp;
//         reverseArray(arr, start + 1, end - 1);
//     }
// }
// // 在main函数中调用
// reverseArray(a, 0, n - 1);

    // //逆序数组(方法3)递归方法的非递归等价方法
    // int left = 0;
    // int right = n - 1; 
    // while (left < right) {          
    //     temp = a[left];
    //     a[left] = a[right];
    //     a[right] = temp;
    //     left++;
    //     right--;
    // }

    // 输出数组
    for(i = 0; i < n; i++) {
        if(i == 0){
            printf("%d", a[i]);
        }else{
            printf(" %d", a[i]);
        }
    }
    printf("\n");
    return 0;
}