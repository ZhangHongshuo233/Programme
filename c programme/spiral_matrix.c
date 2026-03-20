#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(){

// 所谓“螺旋方阵”，是指对任意给定的N，将1到N×N的数字从左上角第1个格子开始，按顺时针螺旋方向顺序填入N×N的方阵里。本题要求构造这样的螺旋方阵。
// 输入格式：
// 输入在一行中给出一个正整数N（<10）。
// 输出格式：
// 输出N×N的螺旋方阵。每行N个数字，每个数字占3位。
    int n;
    scanf("%d",&n);
    int a[n][n];
    int i,j;
    int num=1; 
    int top=0,bottom=n-1,left=0,right=n-1;

    //方法一：填充一整圈（不包含每条边的最后一个元素）
    while(num<=n*n){    
        for(i=left;i<right;i++){
            a[top][i]=num++;
        }
        for(i=top;i<bottom;i++){
            a[i][right]=num++;
        }
        for(i=right;i>left;i--){
            a[bottom][i]=num++;
        }   
        for(i=bottom;i>top;i--){
            a[i][left]=num++;
        }

        //当n为奇数时，最后会剩下中心的一个元素未填充
        if(top==bottom&&left==right){
            a[top][left]=num++;
        }

        //一圈填充完后，统一缩小边界
        top++;
        left++;
        bottom--;
        right--;
    }

    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            printf("%3d",a[i][j]);
        }
        printf("\n");
    }
    return 0;
} 