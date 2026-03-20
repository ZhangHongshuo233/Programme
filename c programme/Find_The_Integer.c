//本题要求从输入的N个整数中查找给定的X。如果找到，输出X的位置（从0开始数）；如果没有找到，输出“Not Found”。
#include <stdio.h>
#define MAXN 20
int main()
{
    int i, n, x, found = 0;//found标记是否找到
    int a[MAXN];

    //读入数组元素个数、要查找的整数X及元素值
    scanf("%d","%d", &n, &x);
    for(i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }
   
    //查找X在数组中的位置
    for(i=0;i<n;i++){
        if(a[i]==x){
            printf("%d\n",i);
            //标记为已找到
            found = 1;
            //退出循环
            break;
        }
    }

    //如果没有找到，输出“Not Found”
    if(!found){
        printf("Not Found\n");
    }
    return 0;
}