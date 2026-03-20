#include<stdio.h>
#define MAXN 10
int main(){
    int i,j,n,x;
    int a[MAXN];
    int key;
    //读入数组元素个数及元素值
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    scanf("%d",&x);
    //key初始化为n，处理x大于数组中所有元素的极端情况
    int key=n;
    //插入排序
    for(i=0;i<n;i++){
        if(a[i]>x){
            key=i;
            break;
        }
    }
    for(j=n;j>key;j--){
        a[j]=a[j-1];
    }
    a[key]=x;

// //更简洁版
//     int key =x;
//     j=n-1;
//     while(j>=0 && a[j]>key){
//         a[j+1]=a[j];
//         j--;
//     }
//     a[j+1]=key;
    //输出插入x后的数组
    for(i=0;i<=n;i++){
        printf("%d ",a[i]);
    }       
    return 0;
}
//Optimized version 
// #include<stdio.h>
// #define MAXN 10  // 数组最大容量

// int main(){
//     int i, j, n, x;
//     int a[MAXN];
//     int key = n;  // 合并声明与初始化，默认插入到末尾

//     // 读入数组元素个数（需检查不超过最大容量）
//     printf("请输入数组元素个数n（n < %d）：", MAXN);
//     scanf("%d", &n);
//     if (n < 0 || n >= MAXN) {  // 检查n的合法性（避免初始数组越界）
//         printf("数组元素个数超出最大容量！\n");
//         return 1;  // 异常退出
//     }

//     // 读入数组元素（假设数组已按升序排列）
//     printf("请输入%d个有序整数（升序）：", n);
//     for(i = 0; i < n; i++){
//         scanf("%d", &a[i]);
//     }

//     // 读入待插入元素
//     printf("请输入待插入的整数x：");
//     scanf("%d", &x);

//     // 检查插入后是否超出最大容量（n+1 ≤ MAXN）
//     if (n + 1 > MAXN) {
//         printf("插入后数组超出最大容量！\n");
//         return 1;  // 异常退出
//     }

//     // 寻找插入位置（第一个大于x的元素索引）
//     for(i = 0; i < n; i++){
//         if(a[i] > x){
//             key = i;
//             break;
//         }
//     }

//     // 元素后移：从原数组末尾（索引n-1）的下一位（n）开始，直到key位置
//     for(j = n; j > key; j--){
//         a[j] = a[j - 1];
//     }

//     // 插入x
//     a[key] = x;

//     // 输出插入后的数组
//     printf("插入后的数组：");
//     for(i = 0; i <= n; i++){
//         printf("%d ", a[i]);
//     }

//     return 0;
// }

