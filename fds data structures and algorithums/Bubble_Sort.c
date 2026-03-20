#include <stdio.h>
#define MAXN 10

int main()
{
    int i, j, n, temp;
    int a[MAXN];
//读入数组元素个数及元素值
    scanf("%d", &n);
    for(i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }
//冒泡排序
//  外层循环控制排序轮数，共需进行n-1轮排序
    for(i = 1; i < n; i++){
        //内层循环进行相邻元素比较交换，每轮比较次数逐渐减少
        for(j = 0; j < n - i; j++){
            if(a[j] > a[j + 1]){
                //进行交换
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
//输出排序后的数组元素，确保行末无多余空格
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
//解析：冒泡排序通过相邻元素比较并交换，将大元素逐步 “冒泡” 到末尾。外层循环控制排序轮数，内层循环进行相邻元素比较交换。输出逻辑与选择法排序一致，确保行末无多余空格。
/*也可以定义冒泡函数
void bubblesort(int arr[],int n){
    int i,j,temp;
    int swapped;        //标记是否发生交换
    for(i=0;i<n-1;i++){
        swapped =0;
        for(j=1;j<n-i;j++){
            if(arr[j]<arr[j-1]){
                //进行交换
                temp= arr[j];
                arr[j]=arr[j-1];
                arr[j-1]=temp;
                swapped=1;  //发生交换，置为1
                }
            }
        }
        //如果某轮没有发生交换，说明数组已排序完成，提前退出    
        if(swapped=0)
            break;
    }
*/