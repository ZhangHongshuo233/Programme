//本题要求编写程序，求一个给定的m×n矩阵各行元素之和。
#include <stdio.h>
#define MAXM 6
int sum_row(int a[][MAXM], int n, int row) {
    int sum = 0;
    int j;
    for (j = 0; j < n; j++) {
        sum += a[row][j];
    }
    return sum;
}
int main(){
    int m,n,i,j;
    scanf("%d %d",&m,&n);
    int a[MAXM][MAXM];
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            scanf("%d",&a[i][j]);
        }
    }
    for(i=0;i<m;i++){
        printf("%d\n",sum_row(a,n,i));
    }
}