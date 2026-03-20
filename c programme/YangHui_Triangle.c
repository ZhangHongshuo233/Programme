#include<stdio.h>
#define MAXN 10
int main(){
    int a[MAXN][MAXN]={0};
    int i,j;
    int N;
    scanf("%d",&N);
    // Initialize the first and the last element
    for(i=0;i<N;i++){
        a[i][0]=1;
        a[i][i]=1;
    }
    // Calculate the values in Yang Hui Triangle
    for(i=2;i<N;i++){
        for(j=1;j<i;j++){
            a[i][j]=a[i-1][j-1]+a[i-1][j];
        }
    }
    // Print the Yang Hui Triangle
    for(i=0;i<N;i++){
        // Print leading spaces for formatting
        for(j=0;j<N-i-1;j++){
            printf(" ");
        }
        // Print the values in the row
        for(j=0;j<=i;j++){
            printf("%4d",a[i][j]);
        }
        if(i!=N-1)
        printf("\n");
    }

}
/*本题要求按照规定格式打印前N行杨辉三角。

输入格式：
输入在一行中给出N（1≤N≤10）。

输出格式：
以正三角形的格式输出前N行杨辉三角。每个数字占固定4位。
*/