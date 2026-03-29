#include <stdio.h>
#define MAXN 10

int main()
{
    int i, index, k, n, temp;
    int a[MAXN];
//读入数组元素个数及元素值
    scanf("%d", &n);
    for(i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }
//选择法排序
// 外层循环控制排序轮数，共需进行n-1轮排序
    for(k = 0; k < n-1; k++){
        index = k;
        for(i = k + 1; i < n; i++){
            //查找最小元素的索引
            if(a[i] < a[index]){
                index = i;
            }
        }
        //将找到的最小元素与当前位置元素交换
        temp = a[k];
        a[k] = a[index];
        a[index] = temp;
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
//解析：选择法排序的核心是每次从待排序区间中找到最小元素的索引，与当前起始位置元素交换。
//外层循环控制排序轮数，内层循环查找最小元素索引，最后通过交换完成排序。
//输出时通过判断是否为第一个元素来控制空格，避免行末多余空格。