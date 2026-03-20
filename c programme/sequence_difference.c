/*本题要求编写程序，对顺序读入的n个整数，
顺次计算后项减前项之差，并按每行三个元素的格式输出结果。
输入格式：
输入的第一行给出正整数n（1<n≤10）。随后一行给出n个整数，其间以空格分隔。
输出格式：
顺次计算后项减前项之差，并按每行三个元素的格式输出结果。
数字间空一格，行末不得有多余空格。*/
#include <stdio.h>
#include <stdlib.h>
#define MAXN 10
int main(){
    int n,i;
    scanf("%d",&n);
    int*a=(int*)malloc(n*sizeof(int));
    int*diff=(int*)malloc((n-1)*sizeof(int));
    //读入n个整数
    for(i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    //计算后项减前项之差
    for(i=0;i<n-1;i++){
        diff[i]=a[i+1]-a[i];
    }
    //按每行三个元素的格式输出结果
    for(i=0;i<n-1;i++){
        printf("%d",diff[i]);
        if((i+1)%3==0){
            if((n-1)%3!=0){
                printf("\n");
            }
            else if(i+1<n-1){
                printf("\n");
            }
        }
        else if(i!=n-2){
            printf(" ");
        }
    }
    free(a);
    free(diff);
    a=NULL;
    diff=NULL;
    return 0;

}